#include "PeakAEnginePCH.h"
#include "NetworkManager.h"

#include "GameNetworkMessage.h"
#include "PlayerState.h"
#include "PartyImpl.h"

#include "Managers.h"

using namespace Party;

void NetworkManager::Initialize()
{
    Logger::LogInfo("[NetworkManager] Initializing NetworkManager.\n");

    auto& partyManager = PartyManager::GetSingleton();
    PartyError err;

    if (m_partyInitialized == false)
    {
        // Initialize PlayFab Party
        err = partyManager.Initialize(PLAYFABMANAGER->GetTitleId().c_str());
        if (PARTY_FAILED(err))
        {
            LogPartyError("[NetworkManager] Initialize failed: \n", err);
            return;
        }

        m_partyInitialized = true;
    }

    CreateLocalUser();
}

void NetworkManager::CreateAndConnectToNetwork(const char* inviteId, std::function<void(std::string)> onNetworkCreated)
{
    Logger::LogInfo("[NetworkManager] CreateAndConnectToNetwork()");

    PartyNetworkConfiguration cfg = {};

    // Setup the network to allow 8 single-device players of any device type
    cfg.maxDeviceCount = 8;
    cfg.maxDevicesPerUserCount = 1;
    cfg.maxEndpointsPerDeviceCount = 1;
    cfg.maxUserCount = 8;
    cfg.maxUsersPerDeviceCount = 1;

    // Setup the network invitation configuration to use the network id as an invitation id and allow anyone to join.
    PartyInvitationConfiguration invitationConfiguration
    {
        inviteId,                                   // invitation identifier
        PartyInvitationRevocability::Anyone,        // revokability
        0,                                          // authorized user count
        nullptr                                     // authorized user list
    };

    PartyNetworkDescriptor networkDescriptor = {};

    // Create a new network descriptor
    PartyError err = PartyManager::GetSingleton().CreateNewNetwork(
        m_localUser,                                                     // Local User
        &cfg,                                         // Network Config
        0,                                                       // Region List Count
        nullptr,                                                    // Region List
        &invitationConfiguration,                   // Invitation configuration
        nullptr,                                                    // Async Identifier
        &networkDescriptor,                                                     // OUT network descriptor
        nullptr                                     // Applied initial invitation identifier
    );

    if (PARTY_FAILED(err))
    {
        LogPartyError("[NetworkManager] CreateNewNetwork failed: ", err);
        return;
    }

    // Connect to the new network
    if (InternalConnectToNetwork(inviteId, networkDescriptor))
    {
        m_state = NetworkManagerState::WaitingForNetwork;
        m_onNetworkCreated = onNetworkCreated;
    }
}

void NetworkManager::ConnectToNetwork(const char* inviteId, const char* descriptor, std::function<void(void)> onNetworkConnected)
{
    Logger::LogInfo("[NetworkManager] ConnectToNetwork()");

    PartyNetworkDescriptor networkDescriptor = {};

    // Deserialize the remote network's descriptor
    PartyError err = PartyManager::DeserializeNetworkDescriptor(descriptor, &networkDescriptor);

    if (PARTY_FAILED(err))
    {
        LogPartyError("[NetworkManager] ConnectToNetwork failed to deserialize descriptor: ", err);
        return;
    }

    // Connect to the remote network
    if (InternalConnectToNetwork(inviteId, networkDescriptor))
    {
        m_state = NetworkManagerState::WaitingForNetwork;
        m_onNetworkConnected = onNetworkConnected;
    }
}

void NetworkManager::SendGameMessage(const GameNetworkMessage& message)
{
    if (m_localEndpoint && m_state == NetworkManagerState::NetworkConnected)
    {
        auto packet = message.Serialize();

        // Form the data packet into a data buffer structure
        PartyDataBuffer data[] = {
            {
                static_cast<const void*>(packet.data()),
                static_cast<uint32_t>(packet.size())
            },
        };

        PartySendMessageOptions deliveryOptions;

        // ShipInput and ShipData messages don't need to be sent reliably
        // or sequentially, but the rest are needed for gameplay
        switch (message.MessageType())
        {
        case GameMessageType::ShipInput:
        case GameMessageType::ShipData:
            deliveryOptions = PartySendMessageOptions::Default;
            break;
        default:
            deliveryOptions = PartySendMessageOptions::GuaranteedDelivery |
                PartySendMessageOptions::SequentialDelivery;
        }

        // Send out the message to all other peers
        PartyError err = m_localEndpoint->SendMessage(
            0,                                      // endpoint count; 0 = broadcast
            nullptr,                                // endpoint list
            deliveryOptions,                        // send message options
            nullptr,                                // configuration
            1,                                      // buffer count
            data,                                   // buffer
            nullptr                                 // async identifier
        );

        if (PARTY_FAILED(err))
        {
            LogPartyError("[NetworkManager] Failed To SendMessage: ", err);
        }
    }
}

void NetworkManager::SendTextMessage(const std::string& text)
{
    if (m_localChatControl != nullptr)
    {
        Logger::LogInfo("[NetworkManager] Send text message: " + text);

        std::vector<PartyChatControl*> targets;

        for (const auto& item : m_chatControls)
        {
            PartyLocalChatControl* local = nullptr;

            item.second->GetLocal(&local);

            if (local == nullptr)
            {
                targets.push_back(item.second);
            }
        }

        PartyError err = m_localChatControl->SendText(
            static_cast<uint32_t>(targets.size()),  // Count of target controls
            targets.data(),                         // Target controls
            text.c_str(),                           // Text to synthesize
            0,                                      // Data buffer size
            nullptr                                 // Data buffer
        );

        if (PARTY_FAILED(err))
        {
            LogPartyError("[NetworkManager] Failed to SendText: ", err);
        }

        // Toast the text on the screen
        //ToDoo: Chatbox?
        Logger::LogInfo("[CHAT] " + DisplayNameFromChatControl(m_localChatControl) + ": " + text);
    }
}

void NetworkManager::LeaveNetwork(std::function<void(void)> onNetworkDestroyed)
{
    Logger::LogInfo("[NetworkManager] LeaveNetwork()");

    if (m_state != NetworkManagerState::Leaving && m_network != nullptr)
    {
        m_state = NetworkManagerState::Leaving;
        m_onNetworkDestroyed = onNetworkDestroyed;

        // First destroy the chat control
        PartyLocalDevice* localDevice = nullptr;

        // Retrieve the local device
        auto err = PartyManager::GetSingleton().GetLocalDevice(&localDevice);

        if (PARTY_FAILED(err))
        {
            LogPartyError("[NetworkManager] GetLocalDevice failed: ", err);
            m_network->LeaveNetwork(nullptr);
            return;
        }

        err = localDevice->DestroyChatControl(m_localChatControl, nullptr);

        if (PARTY_FAILED(err))
        {
            LogPartyError("[NetworkManager] DestroyChatControl failed: ", err);
            m_network->LeaveNetwork(nullptr);
        }
    }
    else
    {
        if (onNetworkDestroyed != nullptr)
        {
            onNetworkDestroyed();
        }
    }
}

bool NetworkManager::InternalConnectToNetwork(const char* inviteId, Party::PartyNetworkDescriptor& descriptor)
{
    // This portion of connecting to the network is the same for
    // both creating a new and joining an existing network.

    PartyError err = PartyManager::GetSingleton().ConnectToNetwork(
        &descriptor,                                // Network descriptor
        nullptr,                                    // Async identifier
        &m_network                                  // OUT network
    );

    if (PARTY_FAILED(err))
    {
        LogPartyError("[NetworkManager] ConnectToNetwork failed: ", err);
        return false;
    }

    // Authenticate the local user on the network so we can participate in it
    err = m_network->AuthenticateLocalUser(
        m_localUser,                                // Local user
        inviteId,                                   // Invite value
        nullptr                                     // Async identifier
    );

    if (PARTY_FAILED(err))
    {
        LogPartyError("[NetworkManager] AuthenticateLocalUser failed: ", err);
        return false;
    }

    CreateLocalChatControl();

    // Connect the local user chat control to the network so we can use VOIP
    err = m_network->ConnectChatControl(
        m_localChatControl,                         // Local chat control
        nullptr                                     // Async identifier
    );

    if (PARTY_FAILED(err))
    {
        LogPartyError("[NetworkManager] ConnectChatControl failed: ", err);
        return false;
    }

    // Establish a network endpoint for game message traffic
    err = m_network->CreateEndpoint(
        m_localUser,                                // Local user
        0,                                          // Property Count
        nullptr,                                    // Property name keys
        nullptr,                                    // Property Values
        nullptr,                                    // Async identifier
        &m_localEndpoint                            // OUT local endpoint
    );

    if (PARTY_FAILED(err))
    {
        LogPartyError("[NetworkManager] Failed to CreateEndpoint: ", err);
        return false;
    }

    return true;
}

void NetworkManager::CreateLocalUser()
{
    if (m_localUser == nullptr)
    {
        auto& partyManager = PartyManager::GetSingleton();
        PartyError err;
        std::string entityId = PLAYFABMANAGER->GetEntityKey().Id;
        std::string entityToken = PLAYFABMANAGER->GetEntityToken();

        // Create a local user object
        err = partyManager.CreateLocalUser(
            entityId.c_str(),                                   // User id
            entityToken.c_str(),                                // User entity token
            &m_localUser                                // OUT local user object
        );

        if (PARTY_FAILED(err))
        {
            LogPartyError("[NetworkManager] CreateLocalUser failed: ", err);
            return;
        }
    }
}

void NetworkManager::CreateLocalChatControl()
{
    if (m_localChatControl == nullptr)
    {
        auto& partyManager = PartyManager::GetSingleton();
        PartyError err;
        PartyLocalDevice* localDevice = nullptr;

        // Retrieve the local device
        err = partyManager.GetLocalDevice(&localDevice);

        if (PARTY_FAILED(err))
        {
            LogPartyError("[NetworkManager] GetLocalDevice failed: ", err);
            return;
        }

        // Create a chat control for the local user on the local device
        err = localDevice->CreateChatControl(
            m_localUser,                                // Local user object
            m_languageCode.c_str(),                     // Language id
            nullptr,                                    // Async identifier
            &m_localChatControl                         // OUT local chat control
        );

        if (PARTY_FAILED(err))
        {
            LogPartyError("[NetworkManager] CreateChatControl failed: ", err);
            return;
        }

        // Use automatic settings for the audio input device
        err = m_localChatControl->SetAudioInput(
            PartyAudioDeviceSelectionType::SystemDefault,   // Selection type
            nullptr,                                        // Device id
            nullptr                                         // Async identifier
        );

        if (PARTY_FAILED(err))
        {
            LogPartyError("[NetworkManager] SetAudioInput failed: ", err);
            return;
        }

        // Use automatic settings for the audio output device
        err = m_localChatControl->SetAudioOutput(
            PartyAudioDeviceSelectionType::SystemDefault,   // Selection type
            nullptr,                                        // Device id
            nullptr                                         // Async identifier
        );

        if (PARTY_FAILED(err))
        {
            LogPartyError("[NetworkManager] SetAudioOutput failed: ", err);
        }

        // Get the available list of text to speech profiles
        err = m_localChatControl->PopulateAvailableTextToSpeechProfiles(nullptr);

        if (PARTY_FAILED(err))
        {
            LogPartyError("[NetworkManager] Populating available TextToSpeechProfiles failed: ", err);
        }
    }
}

void NetworkManager::Destroy()
{
    Logger::LogInfo("[NetworkManager] Shutting down...");

    m_state = NetworkManagerState::Initialize;

    // This cleans up everything allocated in Initialize() and
    // should only be used when done with networking
    PartyManager::GetSingleton().Cleanup();

    m_localChatControl = nullptr;
    m_localEndpoint = nullptr;
    m_network = nullptr;
    m_localUser = nullptr;
    m_partyInitialized = false;
}

void NetworkManager::Update()
{
    uint32_t count;
    PartyStateChangeArray changes;

    if (m_partyInitialized == false)
    {
        return;
    }

    // Start processing messages from PlayFab Party
    auto err = PartyManager::GetSingleton().StartProcessingStateChanges(
        &count,
        &changes
    );

    if (PARTY_FAILED(err))
    {
        LogPartyError("[NetworkManager] StartProcessingStateChanges failed: ", err);
        return;
    }

    for (uint32_t i = 0; i < count; i++)
    {
        auto change = changes[i];

        switch (change->stateChangeType)
        {
        case PartyStateChangeType::CreateNewNetworkCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::CreateNewNetworkCompleted");
            auto result = static_cast<const PartyCreateNewNetworkCompletedStateChange*>(change);
            if (result->result == PartyStateChangeResult::Succeeded)
            {
                Logger::LogSuccess("[NetworkManager] CreateNewNetworkCompleted: SUCCESS");
                PartyString entityId;
                result->localUser->GetEntityId(&entityId);
                Logger::LogSuccess("[NetworkManager] CreateNewNetworkCompleted: EntityId: " + std::string{entityId});
            }
            else
            {
                Logger::LogError("[NetworkManager] Failed: ");
                LogPartyError("[NetworkManager] Error Detail: ", result->errorDetail);
                //Managers::Get<GameStateManager>()->ResetGame("Unable to create network");
            }
            break;
        }
        case PartyStateChangeType::ConnectToNetworkCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::ConnectToNetworkCompleted");
            auto result = static_cast<const PartyConnectToNetworkCompletedStateChange*>(change);
            if (result->result == PartyStateChangeResult::Succeeded)
            {
                Logger::LogSuccess("[NetworkManager] ConnectToNetworkCompleted: SUCCESS");
                m_state = NetworkManagerState::NetworkConnected;
                // Callback if ConnectToNetwork() was called
                if (m_onNetworkConnected)
                {
                    m_onNetworkConnected();
                }
                // Callback if CreateAndConnectToNetwork() was called
                if (m_onNetworkCreated)
                {
                    char descriptor[c_maxSerializedNetworkDescriptorStringLength + 1] = {};

                    // Serialize our local network descriptor for other peers to use
                    err = PartyManager::SerializeNetworkDescriptor(
                        &result->networkDescriptor,
                        descriptor
                    );

                    if (PARTY_FAILED(err))
                    {
                        LogPartyError("[NetworkManager] Failed to serialize network descriptor: ", err);
                        m_onNetworkCreated(std::string());
                    }

                    Logger::LogInfo("[Serialized value: ]" + std::string{ descriptor });
                    // Callback with the descriptor to be shared with connecting clients
                    m_onNetworkCreated(std::string(descriptor));
                }
            }
            else
            {
                Logger::LogError("[NetworkManager] Failed: ");
                LogPartyError("[NetworkManager] Error Detail: ", result->errorDetail);
                //Managers::Get<GameStateManager>()->ResetGame("Unable to connect to network");
            }
            break;
        }
        case PartyStateChangeType::CreateEndpointCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::CreateEndpointCompleted");
            auto result = static_cast<const PartyCreateEndpointCompletedStateChange*>(change);
            if (result->result == PartyStateChangeResult::Succeeded)
            {
                Logger::LogSuccess("[NetworkManager] CreateEndpointCompleted: SUCCESS");
            }
            else
            {
                Logger::LogError("[NetworkManager] Failed: ");
                LogPartyError("[NetworkManager] Error Detail: ", result->errorDetail);
                //Managers::Get<GameStateManager>()->ResetGame("Unable to establish network endpoint");
            }
            break;
        }
        case PartyStateChangeType::EndpointCreated:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::EndpointCreated");
            auto result = static_cast<const PartyEndpointCreatedStateChange*>(change);
            PartyString user = nullptr;

            err = result->endpoint->GetEntityId(&user);

            if (PARTY_FAILED(err) || user == nullptr)
            {
                LogPartyError("[NetworkManager] Unable to retrieve user id from endpoint: ", err);
            }
            else
            {
                // Send out our info packets to any new connections so
                // they'll know about us.
                auto playerState = GAMESTATE->GetPlayerState(PLAYFABMANAGER->GetEntityKey().Id);
                auto displayName = playerState->GetDisplayName();

                SendGameMessage(GameNetworkMessage(GameMessageType::PlayerJoin,
                    displayName));

                TIME->AddTimer(std::make_shared<FrameCounter>(1, [=] 
                    {
                    SendGameMessage(GameNetworkMessage(GameMessageType::PlayerState,
                        playerState->SerializePlayerStateData()));
                    }));
                

                Logger::LogInfo("[NetworkManager] Established endpoint with user " + std::string{ user } + " (" + displayName + ")");

            }
            break;
        }
        case PartyStateChangeType::EndpointDestroyed:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::EndpointDestroyed");
            auto result = static_cast<const PartyEndpointDestroyedStateChange*>(change);

            Logger::LogInfo("Endpoint is \n" + (result->endpoint == m_localEndpoint) ? "local" : "remote");
            LogPartyError("[NetworkManager] Error Detail: ", result->errorDetail);

            if (result->endpoint == m_localEndpoint)
            {
                // Our endpoint was disconnected
                m_localEndpoint = nullptr;

                auto playerState = GAMESTATE->GetPlayerState(PLAYFABMANAGER->GetEntityKey().Id);
                auto displayName = playerState->GetDisplayName();

                SendGameMessage(GameNetworkMessage(GameMessageType::PlayerLeave,
                    displayName));
            }
            else
            {
                // Another user has disconnected
                PartyString user = nullptr;
                err = result->endpoint->GetEntityId(&user);

                if (PARTY_FAILED(err))
                {
                    LogPartyError("[NetworkManager] Unable to retrieve user id from endpoint: ", err);
                    break;
                }

                std::string userId(user);
                Logger::LogInfo("[NetworkManager] Another user has disconnected: " + userId);
                GAMESTATE->DestroyPlayerObject(userId);
            }
            break;
        }
        case PartyStateChangeType::EndpointMessageReceived:
        {
            // This is spammy, but can be useful when debugging
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::EndpointMessageReceived");

            auto result = static_cast<const PartyEndpointMessageReceivedStateChange*>(change);
            auto buffer = static_cast<const uint8_t*>(result->messageBuffer);
            auto packet = std::make_shared<GameNetworkMessage>(
                std::vector<uint8_t>(buffer, buffer + result->messageSize)
                );

            PartyString sender = nullptr;
            err = result->senderEndpoint->GetEntityId(&sender);

            if (PARTY_SUCCEEDED(err))
            {
                std::string senderId(sender);

                // Give the message to the game engine
                GAMESTATE->ProcessNetworkMessage(senderId, packet);
            }
            else
            {
                LogPartyError("[NetworkManager] GetEntityId failed: ", err);
            }

            break;
        }
        case PartyStateChangeType::AuthenticateLocalUserCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::AuthenticateLocalUserCompleted");
            auto result = static_cast<const PartyAuthenticateLocalUserCompletedStateChange*>(change);
            if (result->result == PartyStateChangeResult::Succeeded)
            {
                Logger::LogSuccess("[NetworkManager] SUCCESS");
            }
            else
            {
                Logger::LogError("[NetworkManager] Failed: ");
                LogPartyError("[NetworkManager] Error Detail: ", result->errorDetail);
                //Managers::Get<GameStateManager>()->ResetGame("Unable to authenticate local user");
            }
            break;
        }
        case PartyStateChangeType::LocalUserRemoved:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::LocalUserRemoved");
            if (m_state != NetworkManagerState::Leaving)
            {
                Logger::LogWarning("[NetworkManager] Unexpected local user removal!");
            }
            break;
        }
        case PartyStateChangeType::LeaveNetworkCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::LeaveNetworkCompleted");
            m_state = NetworkManagerState::Initialize;
            if (m_onNetworkDestroyed)
            {
                m_onNetworkDestroyed();
            }
            break;
        }
        case PartyStateChangeType::NetworkDestroyed:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::NetworkDestroyed");
            m_network = nullptr;
            if (m_state != NetworkManagerState::Leaving)
            {
                Logger::LogWarning("[NetworkManager] Unexpected network destruction!");
                //Managers::Get<GameStateManager>()->ResetGame("Unexpected network destruction");
            }
            break;
        }
        case PartyStateChangeType::NetworkConfigurationMadeAvailable:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::NetworkConfigurationMadeAvailable");
            break;
        }
        case PartyStateChangeType::RemoteDeviceCreated:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::RemoteDeviceCreated");
            break;
        }
        case PartyStateChangeType::RemoteDeviceJoinedNetwork:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::RemoteDeviceJoinedNetwork");
            break;
        }
        case PartyStateChangeType::RemoteDeviceDestroyed:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::RemoteDeviceDestroyed");
            break;
        }
        case PartyStateChangeType::RemoteDeviceLeftNetwork:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::RemoteDeviceLeftNetwork");
            break;
        }
        case PartyStateChangeType::ChatControlJoinedNetwork:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::ChatControlJoinedNetwork");
            break;
        }
        case PartyStateChangeType::ChatControlLeftNetwork:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::ChatControlLeftNetwork");
            break;
        }
        case PartyStateChangeType::ChatControlDestroyed:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::ChatControlDestroyed");
            auto result = static_cast<const PartyChatControlDestroyedStateChange*>(change);
            PartyString sender = nullptr;
            err = result->chatControl->GetEntityId(&sender);

            if (PARTY_FAILED(err))
            {
                LogPartyError("[NetworkManager] GetEntityId failed: ", err);
            }
            else
            {
                Logger::LogInfo("[NetworkManager] Created ChatControl from: " + std::string{ sender });

                if (result->chatControl == m_localChatControl)
                {
                    Logger::LogInfo("[NetworkManager] Local ChatControl destroyed." + std::string{ sender });
                    m_localChatControl = nullptr;

                    if (m_state == NetworkManagerState::Leaving)
                    {
                        // Continue the LeaveNetwork process
                        m_network->LeaveNetwork(nullptr);
                    }
                }
                else
                {
                    m_chatControls.erase(sender);
                }
            }
            break;
        }
        case PartyStateChangeType::ChatControlCreated:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::ChatControlCreated");
            auto result = static_cast<const PartyChatControlCreatedStateChange*>(change);
            PartyString sender = nullptr;
            err = result->chatControl->GetEntityId(&sender);

            if (PARTY_FAILED(err))
            {
                LogPartyError("[NetworkManager] GetEntityId failed: ", err);
            }
            else
            {
                Logger::LogInfo("[NetworkManager] Created ChatControl for: " + std::string{ sender });
                m_chatControls[sender] = result->chatControl;

                PartyLocalChatControl* local = nullptr;
                err = result->chatControl->GetLocal(&local);

                if (PARTY_FAILED(err))
                {
                    LogPartyError("[NetworkManager] Failed to get LocalChatControl: ", err);
                }
                else if (local == nullptr)
                {
                    Logger::LogInfo("[NetworkManager] ChatControl is remote.");

                    // Remote ChatControl added, set chat permissions
                    err = m_localChatControl->SetPermissions(
                        result->chatControl,
                        PartyChatPermissionOptions::ReceiveAudio |
                        PartyChatPermissionOptions::ReceiveText |
                        PartyChatPermissionOptions::SendAudio
                    );

                    if (PARTY_FAILED(err))
                    {
                        LogPartyError("[NetworkManager] Failed to SetPermissions on ChatControl: ", err);
                    }
                }
            }
            break;
        }
        case PartyStateChangeType::ConnectChatControlCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::ConnectChatControlCompleted");
            auto result = static_cast<const PartyConnectChatControlCompletedStateChange*>(change);
            if (result->result == PartyStateChangeResult::Succeeded)
            {
                //SetCognitiveServicesEnabled(m_enableCognitiveServices);
                Logger::LogSuccess("[NetworkManager] Succeeded.");
            }
            else
            {
                Logger::LogError("[NetworkManager] Failed: ");
                LogPartyError("[NetworkManager] Error Detail: ", result->errorDetail);
                //Managers::Get<ScreenManager>()->ShowError("Voice chat failed");
            }
            break;
        }
        case PartyStateChangeType::CreateChatControlCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::CreateChatControlCompleted");
            auto result = static_cast<const PartyCreateChatControlCompletedStateChange*>(change);
            if (result->result == PartyStateChangeResult::Succeeded)
            {
                Logger::LogSuccess("[NetworkManager] Succeeded.");
            }
            else
            {
                Logger::LogError("[NetworkManager] Failed: ");
                LogPartyError("[NetworkManager] Error Detail: ", result->errorDetail);
                //Managers::Get<ScreenManager>()->ShowError("Voice chat failed");
            }
            break;
        }
        case PartyStateChangeType::DestroyChatControlCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::DestroyChatControlCompleted");
            auto result = static_cast<const PartyDestroyChatControlCompletedStateChange*>(change);
            if (result->result == PartyStateChangeResult::Succeeded)
            {
                Logger::LogSuccess("[NetworkManager] Succeeded.");
            }
            else
            {
                Logger::LogError("[NetworkManager] Failed: ");
                LogPartyError("[NetworkManager] Error Detail: ", result->errorDetail);
            }
        }
        case PartyStateChangeType::LocalChatAudioInputChanged:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::LocalChatAudioInputChanged");
            auto result = static_cast<const PartyLocalChatAudioInputChangedStateChange*>(change);
            if (PARTY_FAILED(result->errorDetail))
            {
                LogPartyError("[NetworkManager] Error Detail: ", result->errorDetail);
            }
            break;
        }
        case PartyStateChangeType::SetChatAudioInputCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::SetChatAudioInputCompleted");
            auto result = static_cast<const PartySetChatAudioInputCompletedStateChange*>(change);
            if (result->result == PartyStateChangeResult::Succeeded)
            {
                Logger::LogSuccess("[NetworkManager] Succeeded.");
            }
            else
            {
                Logger::LogError("[NetworkManager] Failed.");
                //Managers::Get<ScreenManager>()->ShowError("Voice chat failed");
            }
            break;
        }
        case PartyStateChangeType::SetChatAudioOutputCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::SetChatAudioOutputCompleted");
            auto result = static_cast<const PartySetChatAudioOutputCompletedStateChange*>(change);
            if (result->result == PartyStateChangeResult::Succeeded)
            {
                Logger::LogSuccess("[NetworkManager] Succeeded.");
            }
            else
            {
                Logger::LogError("[NetworkManager] Failed: ");
                LogPartyError("[NetworkManager] Error Detail: ", result->errorDetail);
            }
            break;
        }
        case PartyStateChangeType::LocalChatAudioOutputChanged:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::LocalChatAudioOutputChanged");
            auto result = static_cast<const PartyLocalChatAudioOutputChangedStateChange*>(change);
            if (PARTY_FAILED(result->errorDetail))
            {
                LogPartyError("[NetworkManager] Error Detail: ", result->errorDetail);
            }
            break;
        }
        case PartyStateChangeType::ChatTextReceived:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::ChatTextReceived.");
            auto result = static_cast<const PartyChatTextReceivedStateChange*>(change);

            // Toast the text on the screen
            std::string message;

            // First look for translations
            if (result->translationCount > 0)
            {
                // Since we only have one local chat control, there will only be one translation
                if (result->translations[0].result == PartyStateChangeResult::Succeeded)
                {
                    message = result->translations[0].translation;
                }
                else
                {
                    Logger::LogError("[NetworkManager] Something went wrong translating the ChatTextReceived.");
                }
            }

            if (message.empty())
            {
                message = result->chatText;
            }

            // Toast the text on the screen
                 //ToDoo: Chatbox?
            Logger::LogInfo("[CHAT] " + DisplayNameFromChatControl(result->senderChatControl) + ": " + message);
            Logger::LogInfo("NetworkManager: Chat Text: " + std::string{ result->chatText });

            break;
        }
        case PartyStateChangeType::VoiceChatTranscriptionReceived:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::VoiceChatTranscriptionReceived.");
            auto result = static_cast<const PartyVoiceChatTranscriptionReceivedStateChange*>(change);

            if (PARTY_FAILED(result->errorDetail))
            {
                LogPartyError("[NetworkManager] Error Detail: ", err);
            }
            if (result->result != PartyStateChangeResult::Succeeded)
            {
                Logger::LogError("[NetworkManager] Something went wrong receiving the VoiceChatTranscription.");
            }
            else if (result->transcription == nullptr)
            {
                Logger::LogError("[NetworkManager] Transcription is null");
            }
            else
            {
                // Toast the text on the screen
                std::string message;

                // First look for translations
                if (result->translationCount > 0)
                {
                    // Since we only have one local chat control, there will only be one translation
                    if (result->translations[0].result == PartyStateChangeResult::Succeeded)
                    {
                        message = result->translations[0].translation;
                    }
                    else
                    {
                        Logger::LogError("[NetworkManager] Something went wrong translating the VoiceChatTranscription.");
                    }
                }

                if (message.empty())
                {
                    message = result->transcription;
                }

                // Toast the text on the screen
                //ToDoo: Chatbox?
                Logger::LogInfo("[CHAT] " + DisplayNameFromChatControl(result->senderChatControl) + ": " + message);

                Logger::LogInfo("[NetworkManager] Chat Transcription: " + std::string{ result->transcription });
            }
            break;
        }
        case PartyStateChangeType::SynthesizeTextToSpeechCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::SynthesizeTextToSpeechCompleted.");
            //auto result = static_cast<const PartySynthesizeTextToSpeechCompletedStateChange*>(change);
            //LogResult(result);
            break;
        }
        case PartyStateChangeType::SetTextToSpeechProfileCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::SetTextToSpeechProfileCompleted.");
            //auto result = static_cast<const PartySetTextToSpeechProfileCompletedStateChange*>(change);
            //LogResult(result);
            break;
        }
        case PartyStateChangeType::RegionsChanged:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::RegionsChanged.");
            //auto result = static_cast<const PartyRegionsChangedStateChange*>(change);
            //LogResult(result);
            break;
        }
        case PartyStateChangeType::CreateInvitationCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::CreateInvitationCompleted.");
            break;
        }
        case PartyStateChangeType::RevokeInvitationCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::RevokeInvitationCompleted.");
            break;
        }
        case PartyStateChangeType::InvitationCreated:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::InvitationCreated.");
            break;
        }
        case PartyStateChangeType::InvitationDestroyed:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::InvitationDestroyed.");
            break;
        }
        case PartyStateChangeType::PopulateAvailableTextToSpeechProfilesCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::PopulateAvailableTextToSpeechProfilesCompleted.");
            //UpdateTTSProfile();
            break;
        }
        case PartyStateChangeType::SetTranscriptionOptionsCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::SetTranscriptionOptionsCompleted.");
            //auto result = static_cast<const PartySetTranscriptionOptionsCompletedStateChange*>(change);
            //LogResult(result);
            break;
        }
        case PartyStateChangeType::SetTextChatOptionsCompleted:
        {
            Logger::LogInfo("[NetworkManager] PartyStateChangeType::SetTextChatOptionsCompleted.");
            //auto result = static_cast<const PartySetTextChatOptionsCompletedStateChange*>(change);
            //LogResult(result);
            break;
        }
        default:
            Logger::LogWarning("[NetworkManager] PartyStateChange: Event not found.");
            break;
        }
    }

    // Return the processed changes back to the PartyManager
    err = PartyManager::GetSingleton().FinishProcessingStateChanges(count, changes);

    if (PARTY_FAILED(err))
    {
        LogPartyError("[NetworkManager] FinishProcessingStateChanges failed: ", err);
    }
}

std::string NetworkManager::DisplayNameFromChatControl(PartyChatControl* control)
{
    std::string sttuser = "";
    PartyString sender = nullptr;

    auto err = control->GetEntityId(&sender);
    if (PARTY_FAILED(err) || sender == nullptr)
    {
        LogPartyError("[NetworkManager] GetEntityId failed: ", err);
        sttuser = "[ERROR]";
    }
    else
    {
        std::string senderid(sender);

        //// Get the display name of the sender
        auto playerInfo = GAMESTATE->GetPlayerState(senderid);

        if (playerInfo != nullptr)
        {
            sttuser = playerInfo->GetDisplayName();
        }
        else
        {
            sttuser = senderid;
        }
    }

    return sttuser;
}

void NetworkManager::LogPartyError(const std::string& message, PartyError error)
{
    PartyString errString = "";
    PartyGetErrorMessage(error, &errString);

    Logger::LogError(message + errString);
}
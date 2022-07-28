#include "PeakAEnginePCH.h"
#include "Managers.h"

#include "PlayerState.h"

void GameStateManager::ProcessNetworkMessage(const std::string& sender, std::shared_ptr<GameNetworkMessage>& message)
{
    const auto localPeerId = PLAYFABMANAGER->GetEntityKey().Id;

    switch (message->MessageType())
    {
        case GameMessageType::PlayerJoin:
        {
            auto itr = m_peers.find(sender);
            if (itr == m_peers.end())
            {
                if (sender != localPeerId)
                {
                    // Sender != LocalPlayer
                    auto playerState = std::make_shared<PlayerState>(message->StringValue().c_str());
                    playerState->SetPeerId(sender);

                    m_peers[sender] = playerState;

                    Logger::LogInfo("[GameStateManager] Received PlayerInfo for: " + playerState->GetDisplayName());
                }
            }
            else
            {
                // Sender is known
                Logger::LogInfo("[GameStateManager] Received PlayerInfo from known peer: " + sender);
            }
            break;
        }
        case GameMessageType::ObjectMove:
        {
            Logger::LogInfo("[GameStateManager] Received an ObjectMove message from " + sender);
            auto playerState = GetPlayerState(sender);
            if (playerState != nullptr && sender != localPeerId)
            {
                playerState->DeserializePlayerStateData(message->RawData());
            }
            else
            {
                Logger::LogError("[GameStateManager] No PlayerState exists for peer " + sender);
            }
            break;
        }
        case GameMessageType::PlayerLeave:
            Logger::LogInfo("[GameStateManager] Received a PlayerLeave message from " + sender);
            auto playerState = GetPlayerState(sender);
            if (playerState != nullptr && sender != localPeerId)
            {
                auto itr = m_peers.find(sender);
                if (itr == m_peers.end())
                {
                    m_peers[sender] = nullptr;
                }
            }
            else
            {
                Logger::LogError("[GameStateManager] No PlayerState exists for peer " + sender);
            }
            break;
    }
}

std::shared_ptr<PlayerState> GameStateManager::GetPlayerState(const std::string& peer)
{
    if (peer == PLAYFABMANAGER->GetEntityKey().Id)
    {
        // If LocalPlayer
        return m_LocalPlayer;
    }
    else 
    {
        // If not LocalPlayer
        auto itr = m_peers.find(peer);
        if (itr != m_peers.end())
        {
            return (*itr).second;
        }
    }
    return nullptr;
}

void GameStateManager::CreateLocalPlayer()
{
    auto playerState = std::make_shared<PlayerState>(PLAYFABMANAGER->GetUsername().c_str(), true);
    playerState->SetPeerId(PLAYFABMANAGER->GetEntityKey().Id);

    m_LocalPlayer = playerState;
    Logger::LogInfo("[GameStateManager] Received PlayerInfo for: " + playerState->GetDisplayName());
}

void GameStateManager::DestroyPlayerObject(const std::string& userId)
{
    auto itr = m_peers.find(userId);
    if (itr != m_peers.end())
    {
        itr->second = nullptr;
    }
}

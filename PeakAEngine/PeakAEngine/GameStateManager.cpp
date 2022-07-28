#include "PeakAEnginePCH.h"
#include "Managers.h"

#include "ObjectState.h"

void GameStateManager::ProcessNetworkMessage(const std::string& sender, std::shared_ptr<GameNetworkMessage>& message)
{
    const auto localPeerId = PLAYFABMANAGER->GetEntityKey().Id;

    switch (message->MessageType())
    {
        case GameMessageType::PlayerJoin:
        {
            auto itr = m_PeerObjects.find(sender);
            if (itr == m_PeerObjects.end())
            {
                if (sender != localPeerId)
                {
                    //Create Other Player RootObject
                    auto objectState = std::make_shared<ObjectState>(message->StringValue(), sender);

                    m_PeerObjects[sender]["PlayerManager"] = objectState;

                    Logger::LogInfo("[GameStateManager] Received PlayerJoin for: " + objectState->GetDisplayName());
                }
            }
            else
            {
                // Sender is already known
                Logger::LogInfo("[GameStateManager] Received PlayerJoin from known peer: " + sender);
            }
            break;
        }
        case GameMessageType::PlayerLeave:
        {
            Logger::LogInfo("[GameStateManager] Received a PlayerLeave message from " + sender);
            DestroyPeer(sender);
            break;
        }
        case GameMessageType::ObjectCreated:
        {
            Logger::LogInfo("[GameStateManager] Received a ObjectCreated message from " + sender);
            //ToDoo: Handle Object Creation

                

            break;
        }
        case GameMessageType::ObjectUpdated:
        {
            Logger::LogInfo("[GameStateManager] Received an ObjectUpdated message from " + sender + " for object: " + message->ObjectName());
            auto objectState = GetObjectState(sender, message->ObjectName());
            if (objectState != nullptr && sender != localPeerId)
            {
                objectState->DeserializeObjectStateData(message->RawData());
            }
            else
            {
                Logger::LogError("[GameStateManager] No PlayerState exists for peer " + sender);
            }
            break;
        }
        case GameMessageType::ObjectDestroyed:
        {
            //ToDoo: Handle Object Deletion
            break;
        }
    }
}

std::shared_ptr<ObjectState> GameStateManager::GetObjectState(const std::string& peer, const std::string& objName)
{
    if (peer == PLAYFABMANAGER->GetEntityKey().Id)
    {
        // If LocalPlayer
        if (m_LocalObjects.contains(objName))
            return m_LocalObjects[objName];
    }
    else 
    {
        // If not LocalPlayer
        auto peerItr = m_PeerObjects.find(peer);
        if (peerItr != m_PeerObjects.end())
        {
            auto objItr = peerItr->second.find(objName);
            if (objItr != peerItr->second.end())
                return (*objItr).second;
        }
    }
    return nullptr;
}

void GameStateManager::CreateLocalObject()
{
    auto objectState = std::make_shared<ObjectState>(PLAYFABMANAGER->GetUsername().c_str(), PLAYFABMANAGER->GetEntityKey().Id);

    m_LocalObjects["PlayerManager"] = objectState;
    Logger::LogInfo("[GameStateManager] Created local object for " + objectState->GetDisplayName() + " with the name: " + "PlayerManager");
}

void GameStateManager::DestroyObject(const std::string& userId, const std::string& objectName)
{
    auto peerItr = m_PeerObjects.find(userId);
    if (peerItr != m_PeerObjects.end())
    {
        auto objItr = peerItr->second.find(objectName);
        if (objItr != peerItr->second.end())
            objItr->second = nullptr;
    }
}

void GameStateManager::DestroyPeer(const std::string& peer)
{
    auto peerItr = m_PeerObjects.find(peer);
    if (peerItr != m_PeerObjects.end())
    {
        for (auto obj : peerItr->second)
            obj.second = nullptr;

        return;
    }
    Logger::LogError("[GameStateManager] No such peer found: " + peer);
}

#pragma once
#include "Manager.h"

// Included to avoid header dependencies, 
// Whenever you're working with the gamestatemanager, you'll always use a networkmessage with it
#include "GameNetworkMessage.h"

class ObjectState;

struct NetworkEvent 
{
    std::string sender;
    GameNetworkMessage message;
};

class GameStateManager final : public Manager
{
public:
    // PUBLIC FUNCTIONS
    void ProcessNetworkMessage(const std::string& sender, std::shared_ptr<GameNetworkMessage>& message);
    std::shared_ptr<ObjectState> GetObjectState(const std::string& peer, const std::string& objName);

    void ClearQueue();
    const std::vector<NetworkEvent>& GetQueue() const { return m_EventsThisFrame; }

    void CreateObject(std::shared_ptr<ObjectState> obj, int objTypeId, const std::string& peer, const std::string& objectName);
    void CreateLocalObject();
    void DestroyObject(const std::string& peer, const std::string& objectName);
    void DestroyPeer(const std::string& peer);

    void SendMyObjectsToPeer(const std::string& peer);
private:
    //// Functions
    //// Variables
    bool m_IsDebugging{ true };
    std::vector<NetworkEvent> m_EventsThisFrame;

    // map<peerId, map<objName, objState>>
    std::map<std::string, std::map<std::string, std::shared_ptr<ObjectState>>> m_PeerObjects;
    // map<objName, objState>
    std::map<std::string, std::shared_ptr<ObjectState>> m_LocalObjects;
};
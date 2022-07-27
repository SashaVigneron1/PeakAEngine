#pragma once
#include "Manager.h"

// Included to avoid header dependencies, 
// Whenever you're working with the gamestatemanager, you'll always use a networkmessage with it
#include "GameNetworkMessage.h"

class PlayerState;

class GameStateManager final : public Manager
{
public:
    // PUBLIC FUNCTIONS
    void ProcessNetworkMessage(const std::string& sender, std::shared_ptr<GameNetworkMessage>& message);
    std::shared_ptr<PlayerState> GetPlayerState(const std::string& peer);

    void CreateLocalPlayer();
    void DestroyPlayerObject(const std::string& userId);

private:
    //// Functions

    //// Variables
    std::map<std::string, std::shared_ptr<PlayerState>> m_peers;
    std::shared_ptr<PlayerState> m_LocalPlayer;
};
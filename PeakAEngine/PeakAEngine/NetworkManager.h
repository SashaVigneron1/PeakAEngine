#pragma once
#include "Manager.h"
#include "Party.h"

class GameNetworkMessage;

enum class NetworkManagerState
{
    Initialize,
    WaitingForNetwork,
    NetworkConnected,
    Leaving
};

class NetworkManager final : public Manager
{
public:
	// PUBLIC FUNCTIONS
    void Initialize();
    void CreateAndConnectToNetwork(const char* inviteId, std::function<void(std::string)> onNetworkCreated = nullptr);
    void ConnectToNetwork(const char* inviteId, const char* descriptor, std::function<void(void)> onNetworkConnected = nullptr);
    void SendGameMessage(const GameNetworkMessage& message);
    void SendTextMessage(const std::string& text);
    void LeaveNetwork(std::function<void(void)> onNetworkDestroyed = nullptr);
    void Destroy();

    void Update();

    // Language
    //void SetLanguageCode(const char* lang, const char* name);
    const char* GetLanguageCode() { return m_languageCode.c_str(); }
    const char* GetLanguageName() { return m_languageName.c_str(); }

    // Audio
    void ToggleVoiceChat(bool value);

private:
    //// Functions
    bool InternalConnectToNetwork(const char* networkId, Party::PartyNetworkDescriptor& descriptor);
    void CreateLocalUser();
    void CreateLocalChatControl();
    std::string DisplayNameFromChatControl(Party::PartyChatControl* control);

    void LogPartyError(const std::string& message, PartyError error);

    //// Variables
    // Function Pointers
    std::function<void(std::string)> m_onNetworkCreated{nullptr};
    std::function<void(void)> m_onNetworkConnected{ nullptr };
    std::function<void(void)> m_onNetworkDestroyed{ nullptr };

    // Party Variables
    std::map<std::string, Party::PartyChatControl*> m_chatControls;
    Party::PartyLocalEndpoint* m_localEndpoint{ nullptr };
    Party::PartyNetwork* m_network{ nullptr };
    Party::PartyLocalUser* m_localUser{ nullptr };
    Party::PartyLocalChatControl* m_localChatControl{ nullptr };

    // Language Code
    std::string m_languageCode = "en-US";
    std::string m_languageName = "english";

    // Authenticated User
    std::string m_localEntityId{};
    std::string m_localEntityToken{};

    // Other
    NetworkManagerState m_state{};
    bool m_partyInitialized{};
    bool m_enableCognitiveServices{};
};
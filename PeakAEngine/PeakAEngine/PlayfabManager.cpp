#include "PeakAEnginePCH.h"
#include "PlayfabManager.h"

// Global Variable
std::map<std::string, std::string> g_TempDataMap;

// FORWARD DECLARATIONS
void OnSaveUserData(const UpdateUserDataResult& result, void* customData);
void OnSaveUserDataFail(const PlayFabError& error, void* customData);
void OnLoadUserData(const GetUserDataResult& result, void* customData);
void OnLoadUserDataFail(const PlayFabError& error, void* customData);


//********************************
// PUBLIC FUNCTIONS 
//********************************
void PlayfabManager::Init(const std::string& titleId)
{
    PlayFabSettings::staticSettings->titleId = titleId;
    m_AuthenticationContext = std::make_shared<PlayFab::PlayFabAuthenticationContext>();
}
void PlayfabManager::Update()
{
    PlayFabClientAPI::Update();
}
void PlayfabManager::ForceUpdate()
{
    while (PlayFabClientAPI::Update() != 0)
        Sleep(1);
}

void PlayfabManager::RegisterUser(const std::string& username, const std::string& password, const std::string& email)
{
    // Create User
    RegisterPlayFabUserRequest request;
    request.Email = email;
    request.Username = username;
    request.Password = password;
    request.DisplayName = username;
    PlayFabClientAPI::RegisterPlayFabUser(request, 
        [](const RegisterPlayFabUserResult& result, void* /*customData*/)
        {
            Logger::LogSuccess("[NETWORKMANAGER] Successfully created user: " + result.Username);
        }, 
        [](const PlayFabError& error, void* /*customData*/)
        {
            Logger::LogError("[NETWORKMANAGER] Error creating user: " + error.GenerateErrorReport());
        });
}

void PlayfabManager::LoginUser(const std::string& username, const std::string& password)
{
    // Login User
    LoginWithPlayFabRequest request;
    request.Username = username;
    request.Password = password;
    request.TitleId = PlayFabSettings::staticSettings->titleId;
    PlayFabClientAPI::LoginWithPlayFab(request,
        [](const LoginResult& result, void* /*customData*/)
        {
            auto authenticationContext = PLAYFABMANAGER.GetAuthenticationContext();

            authenticationContext->playFabId = result.PlayFabId;
            authenticationContext->entityToken = result.EntityToken->EntityToken;
            authenticationContext->entityType = result.EntityToken->Entity->Type;
            authenticationContext->entityId = result.EntityToken->Entity->Id;
            authenticationContext->clientSessionTicket = result.SessionTicket;

            Logger::LogSuccess("[NETWORKMANAGER] Succesfully logged in.");
        },
        [](const PlayFabError& error, void* /*customData*/)
        {
            Logger::LogError("[NETWORKMANAGER] Error logging in: " + error.GenerateErrorReport());
        });
}

void PlayfabManager::SaveUserData(std::map<std::string, std::string>& dataMap)
{
    UpdateUserDataRequest request;
    request.authenticationContext = m_AuthenticationContext;
    request.Data = dataMap;
    PlayFabClientAPI::UpdateUserData(request, OnSaveUserData, OnSaveUserDataFail);
}

void PlayfabManager::LoadUserData()
{
    GetUserDataRequest request;
    request.authenticationContext = m_AuthenticationContext;
    request.PlayFabId = m_AuthenticationContext->playFabId;
    PlayFabClientAPI::GetUserData(request, OnLoadUserData, OnLoadUserDataFail);
}

const std::map<std::string, std::string>& PlayfabManager::GetDataMap() const
{
    return g_TempDataMap;
}


//********************************
// RESPONSES 
//********************************

void OnSaveUserData(const UpdateUserDataResult& result, void* /*customData*/)
{
    Logger::LogSuccess("[NETWORKMANAGER] Successfully saved user data! Current Data Version: " + std::to_string(result.DataVersion));
}
void OnSaveUserDataFail(const PlayFabError& error, void* /*customData*/)
{
    Logger::LogError("[NETWORKMANAGER] Error saving user data: " + error.GenerateErrorReport());
}

void OnLoadUserData(const GetUserDataResult& result, void* /*customData*/)
{
    g_TempDataMap.clear();

    // Add data to map
    for (const auto& [key, value] : result.Data)
        g_TempDataMap.emplace(key, value.Value);

    Logger::LogSuccess("[NETWORKMANAGER] Successfully loaded user data!");
}
void OnLoadUserDataFail(const PlayFabError& error, void* /*customData*/)
{
    Logger::LogError("[NETWORKMANAGER] Error loading user data: " + error.GenerateErrorReport());
}
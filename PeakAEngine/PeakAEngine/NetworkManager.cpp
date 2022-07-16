#include "PeakAEnginePCH.h"
#include "NetworkManager.h"

// Global Variable
std::map<std::string, std::string> g_TempDataMap;

// FORWARD DECLARATIONS
void OnRegisterUser(const RegisterPlayFabUserResult& result, void* customData);
void OnRegisterUserFail(const PlayFabError& error, void* customData);
void OnLoginUser(const LoginResult& result, void* customData);
void OnLoginUserFail(const PlayFabError& error, void* customData);
void OnSaveUserData(const UpdateUserDataResult& result, void* customData);
void OnSaveUserDataFail(const PlayFabError& error, void* customData);
void OnLoadUserData(const GetUserDataResult& result, void* customData);
void OnLoadUserDataFail(const PlayFabError& error, void* customData);


//********************************
// PUBLIC FUNCTIONS 
//********************************
void NetworkManager::Init(const std::string& titleId)
{
    PlayFabSettings::staticSettings->titleId = titleId;
    m_AuthenticationContext = std::make_shared<PlayFab::PlayFabAuthenticationContext>();
}
void NetworkManager::Update()
{
    PlayFabClientAPI::Update();
}
void NetworkManager::ForceUpdate()
{
    while (PlayFabClientAPI::Update() != 0)
        Sleep(1);
}

void NetworkManager::RegisterUser(const std::string& username, const std::string& password, const std::string& email)
{
    // Create User
    RegisterPlayFabUserRequest request;
    request.Email = email;
    request.Username = username;
    request.Password = password;
    request.DisplayName = username;
    PlayFabClientAPI::RegisterPlayFabUser(request, OnRegisterUser, OnRegisterUserFail);
}

void NetworkManager::LoginUser(const std::string& username, const std::string& password)
{
    // Login User
    LoginWithPlayFabRequest request;
    request.Username = username;
    request.Password = password;
    request.TitleId = PlayFabSettings::staticSettings->titleId;
    PlayFabClientAPI::LoginWithPlayFab(request, OnLoginUser, OnLoginUserFail);
}

void NetworkManager::SaveUserData(std::map<std::string, std::string>& dataMap)
{
    UpdateUserDataRequest request;
    request.authenticationContext = m_AuthenticationContext;
    request.Data = dataMap;
    PlayFabClientAPI::UpdateUserData(request, OnSaveUserData, OnSaveUserDataFail);
}

void NetworkManager::LoadUserData()
{
    GetUserDataRequest request;
    request.authenticationContext = m_AuthenticationContext;
    request.PlayFabId = m_AuthenticationContext->playFabId;
    PlayFabClientAPI::GetUserData(request, OnLoadUserData, OnLoadUserDataFail);
}

const std::map<std::string, std::string>& NetworkManager::GetDataMap() const
{
    return g_TempDataMap;
}


//********************************
// RESPONSES 
//********************************

void OnRegisterUser(const RegisterPlayFabUserResult& result, void* /*customData*/)
{
    Logger::LogSuccess("[NETWORKMANAGER] Successfully created user: " + result.Username);
}
void OnRegisterUserFail(const PlayFabError& error, void* /*customData*/)
{
    Logger::LogError("[NETWORKMANAGER] Error creating user: " + error.GenerateErrorReport());
}

void OnLoginUser(const LoginResult& result, void* /*customData*/)
{
    auto authenticationContext = NETWORKMANAGER.GetAuthenticationContext();

    authenticationContext->playFabId = result.PlayFabId;
    authenticationContext->entityToken = result.EntityToken->EntityToken;
    authenticationContext->entityType = result.EntityToken->Entity->Type;
    authenticationContext->entityId = result.EntityToken->Entity->Id;
    authenticationContext->clientSessionTicket = result.SessionTicket;

    Logger::LogSuccess("[NETWORKMANAGER] Succesfully logged in.");
}
void OnLoginUserFail(const PlayFabError& error, void* /*customData*/)
{
    Logger::LogError("[NETWORKMANAGER] Error logging in: " + error.GenerateErrorReport());
}

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

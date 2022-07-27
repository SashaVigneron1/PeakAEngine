#pragma once
#include "Manager.h"


//ToDo: Swith to forward declarations
//ToDo: Find a way to multithreaded polling for response

#include "playfab/PlayFabAuthenticationApi.h"
#include "playfab/PlayFabAuthenticationContext.h"
#include "playfab/PlayFabError.h"
#include "playfab/PlayFabClientDataModels.h"
#include "playfab/PlayFabClientApi.h"
#include "playfab/PlayFabSettings.h"
#include "playfab/PlayFabApiSettings.h"

using namespace PlayFab;
using namespace ClientModels;


// Forward Declarations
class PlayfabManager final : public Manager
{
public:
	// PUBLIC FUNCTIONS

	void Init(const std::string& titleId);
	void Update();
	void ForceUpdate();
	//void SetTitleId(const std::string& id);

	void RegisterUser(const std::string& username, const std::string& password, const std::string& email = "");
	void LoginUser(const std::string& username, const std::string& password, std::function<void()> functionOnSucces = nullptr);

	void SaveUserData(std::map<std::string, std::string>& dataMap);
	void LoadUserData();

	void ExecuteCloudScript(const std::string& functionName, const Json::Value& functionParameters, std::function<void(ExecuteCloudScriptResult result, void* customData)> functionOnSucces
		, std::function<void(PlayFabError error, void* customData)> functionOnFail);

	const std::map<std::string, std::string>& GetDataMap() const;

	std::shared_ptr<PlayFabAuthenticationContext> GetAuthenticationContext() const { return m_AuthenticationContext; }

	std::string GetTitleId() const;

	// Mutators
	void SetEntityKey(EntityKey key) { m_Entity = key; }
	EntityKey GetEntityKey() const { return m_Entity; }
	void SetEntityToken(const std::string& token) { m_EntityToken = token; }
	std::string GetEntityToken() const { return m_EntityToken; }

	std::string GetUsername() const { return m_Username; }
	void SetUsername(const std::string& name) { m_Username = name; }
private:
	// VARIABLES
	std::shared_ptr<PlayFabAuthenticationContext> m_AuthenticationContext;
	EntityKey m_Entity;
	std::string m_EntityToken;
	std::string m_Username;
};




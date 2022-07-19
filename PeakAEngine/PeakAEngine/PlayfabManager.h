#pragma once
#include "Singleton.h"

#define PLAYFABMANAGER PlayfabManager::GetInstance()

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
class PlayfabManager final : public Singleton<PlayfabManager>
{
public:
	// PUBLIC FUNCTIONS

	void Init(const std::string& titleId);
	void Update();
	void ForceUpdate();
	//void SetTitleId(const std::string& id);

	void RegisterUser(const std::string& username, const std::string& password, const std::string& email = "");
	void LoginUser(const std::string& username, const std::string& password);

	void SaveUserData(std::map<std::string, std::string>& dataMap);
	void LoadUserData();

	const std::map<std::string, std::string>& GetDataMap() const;

	std::shared_ptr<PlayFabAuthenticationContext> GetAuthenticationContext() const { return m_AuthenticationContext; }

private:
	// VARIABLES
	std::shared_ptr<PlayFabAuthenticationContext> m_AuthenticationContext;


};




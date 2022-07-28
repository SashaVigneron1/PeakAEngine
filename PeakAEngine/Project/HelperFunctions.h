#pragma once

#include "PeakAEngine/Managers.h"

#include "PeakAEngine/Scene.h"
#include "RoomSelectorScene.h"
#include "LoginScene.h"
#include "TestScene.h"
#include "GameScene.h"


void InitializeMultiplayer()
{
    PLAYFABMANAGER->Init("68BA8");
}
void InitializeScenes()
{
    // Add Scenes
    Scene* pScene = new TestScene();
    SCENEMANAGER->AddScene("TestScene", pScene);
    pScene = new LoginScene();
    SCENEMANAGER->AddScene("LoginScene", pScene);
    pScene = new RoomSelectorScene();
    SCENEMANAGER->AddScene("RoomSelectorScene", pScene);
    pScene = new GameScene();
    SCENEMANAGER->AddScene("GameScene", pScene);

    SCENEMANAGER->LoadScene("LoginScene", true);
}

void DestroySharedGroup()
{
    // DESTROY SHARED GROUP
    Json::Value functionParams;
    functionParams["roomId"] = "1";
    PLAYFABMANAGER->ExecuteCloudScript("destroy_shared_group", functionParams,
        [](const PlayFab::ClientModels::ExecuteCloudScriptResult& /*result*/, void* /*customData*/) {
            Logger::LogSuccess("[CLOUDSCRIPT] Succesfully destroyed shared group");
        },
        [](const PlayFabError& error, void* /*customData*/)
        {
            Logger::LogError("[CLOUDSCRIPT] Couldn't destroy shared group: " + error.ErrorMessage);
        });

    PLAYFABMANAGER->ForceUpdate();
}
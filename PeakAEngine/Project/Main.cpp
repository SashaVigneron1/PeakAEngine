#include "pch.h"
#include "PeakAEngine/PeakAEngine.h"
#include "PeakAEngine/Scene.h"
#include "PeakAEngine/SceneManager.h"
#include "LoginScene.h"
#include "TestScene.h"

#include "PeakAEngine/PlayfabManager.h"

int main()
{
#ifndef _DEBUG
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
#else
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_SHOW);
#endif


    ENGINE.Initialize();

    PLAYFABMANAGER.Init("68BA8");

    // Add Scenes
    Scene* pScene = new TestScene();
    SCENEMANAGER.AddScene("TestScene", pScene);
    pScene = new LoginScene();
    SCENEMANAGER.AddScene("LoginScene", pScene);

    SCENEMANAGER.LoadScene("LoginScene");

    ENGINE.Run();


    return 0;
}

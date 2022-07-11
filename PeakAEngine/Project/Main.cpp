#include "pch.h"
#include "PeakAEngine/PeakAEngine.h"
#include "PeakAEngine/Scene.h"
#include "PeakAEngine/SceneManager.h"
#include "TestScene.h"

int main()
{
#ifndef _DEBUG
    //HWND hWnd = GetConsoleWindow();
    //ShowWindow(hWnd, SW_HIDE);
#endif


    ENGINE.Initialize();

    // Add Scenes
    Scene* pScene = new TestScene();
    //Scene* pScene2 = new TestScene();

    SCENEMANAGER.AddScene("TestScene", pScene);
    //SCENEMANAGER.AddScene("TestScene2", pScene2);

    //SCENEMANAGER.LoadScene("TestScene2");

    ENGINE.Run();


    return 0;
}

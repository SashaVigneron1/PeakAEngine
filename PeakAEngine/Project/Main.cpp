#include "pch.h"
#include "PeakAEngine/PeakAEngine.h"

#include "HelperFunctions.h"

#ifdef _DEBUG
    #include "vld.h"
#endif

int main()
{
    // Hide/Enable Console
#ifndef _DEBUG
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
#else
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_SHOW);
#endif

    // Initialize
    ENGINE.Initialize();
    InitializeMultiplayer();

    InitializeScenes();

    ENGINE.Run();

    DestroySharedGroup();

    return 0;
}

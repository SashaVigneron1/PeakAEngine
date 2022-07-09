#include "PeakAEnginePCH.h"
#include "PeakAEngine.h"

#include <SDL.h>
#include <gl/glew.h>

#include <chrono>
#include <fstream>
#include <sstream>

#include "RenderManager.h"
#include "Time.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"

void Engine::Initialize()
{
	InitializeSettings();

	m_EngineSettings.GetData(EngineSettings::gameResolutionX.data(), m_ResolutionWidth);
	m_EngineSettings.GetData(EngineSettings::gameResolutionY.data(), m_ResolutionHeight);
	int w, h;
	m_EngineSettings.GetData(EngineSettings::gameWindowSizeX.data(), w);
	m_EngineSettings.GetData(EngineSettings::gameWindowSizeY.data(), h);
	bool maximizeWindow{};
	m_EngineSettings.GetData(EngineSettings::gameWindowMaximized.data(), maximizeWindow);
	bool fullscreen{};
	m_EngineSettings.GetData(EngineSettings::gameFullscreen.data(), fullscreen);

	// Use OpenGL 3.11
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	// Create window
	std::string windowTitle;
	m_EngineSettings.GetData(EngineSettings::gameTitle.data(), windowTitle);
	m_Window = SDL_CreateWindow(
		windowTitle.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w,
		h,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	// Maximize window if it the setting is on
	if (fullscreen)
	{
		// For borderless, use the flag SDL_WINDOW_FULLSCREEN_DESKTOP
		SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN);
	}
	else if (maximizeWindow)
	{
		SDL_MaximizeWindow(m_Window);
	}

	RENDERER.Init(m_Window);
	RESOURCEMANAGER.Init("Resources/");
}

void Engine::Cleanup()
{
	RENDERER.Destroy();

	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Engine::Run()
{
	Initialize();

	auto& renderer = RENDERER;
	auto& timer = TIME;
	auto& input = INPUTMANAGER;
	auto& sceneManager = SCENEMANAGER;

	constexpr float fixedUpdateInterval = 16 / 100.f;
	timer.SetFixedTime(fixedUpdateInterval);
	float fixedUpdateTimer = 0.0f;
	bool isRunning = true;
	while (isRunning)
	{
		const auto startTime = std::chrono::high_resolution_clock::now();
		timer.CalculateTime();
		fixedUpdateTimer += Time::DeltaTime();

		isRunning = input.ProcessInput();
		sceneManager.Update();

		// Fixed Update
		int currFrame = 0;
		while (fixedUpdateTimer >= fixedUpdateInterval && currFrame <= 50)
		{
			sceneManager.FixedUpdate();
			fixedUpdateTimer -= fixedUpdateInterval;
			currFrame++;
		}

		renderer.Render();

		const auto sleepTime = startTime + std::chrono::milliseconds(16) - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleepTime); // In Short: Doesn't work properly because nr of milliseconds are rounded off to floor

		//// Somewhat closer to actual time
		//// Get The Duration We Need To Sleep For
		//const auto sleepTime = startTime + std::chrono::milliseconds(MsPerFrame) - std::chrono::high_resolution_clock::now();
		//// Get The Nr Of Milliseconds
		//auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(sleepTime);
		//int nrNanos = (int)nanoseconds.count();
		//float nrMillis = nrNanos / 1000000.0f;

		//// Sleep
		//std::this_thread::sleep_until(std::chrono::high_resolution_clock::now() + std::chrono::milliseconds((int)round(nrMillis)));
	}

	Cleanup();
}

const Dictionary& Engine::GetSettings() const
{
	return m_EngineSettings;
}

void Engine::InitializeSettings()
{
	// Load default values
	int integer{ 1920 };
	m_EngineSettings.Insert(EngineSettings::gameResolutionX.data(), integer);
	m_EngineSettings.Insert(EngineSettings::gameWindowSizeX.data(), integer);

	integer = 1080;
	m_EngineSettings.Insert(EngineSettings::gameResolutionY.data(), integer);
	m_EngineSettings.Insert(EngineSettings::gameWindowSizeY.data(), integer);

	integer = 3;
	m_EngineSettings.Insert(EngineSettings::renderLayers.data(), integer);

	bool boolean{ true };
	m_EngineSettings.Insert(EngineSettings::gameWindowMaximized.data(), boolean);

	boolean = false;
	m_EngineSettings.Insert(EngineSettings::gameFullscreen.data(), boolean);

	m_EngineSettings.Insert(EngineSettings::resourcePath.data(), std::string("Resources/"));
	m_EngineSettings.Insert(EngineSettings::gameStartScene.data(), std::string("/"));
	m_EngineSettings.Insert(EngineSettings::gameTitle.data(), std::string("Game Made With PeakAEngine"));

	// Load the engineconfig.ini file
	auto fstream = std::ifstream(EngineSettings::engineConfig.data());

	std::cout << "Loading Info...";
	if (!fstream.is_open()) return;
	std::cout << "There is Info...";

	std::string line;
	while (fstream)
	{
		std::getline(fstream, line);
		auto sstream = std::stringstream(line);
		{
			m_EngineSettings.StreamChange(sstream);
		}
	}
}

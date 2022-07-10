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

	// Get Engine Settings
	//// WINDOW
	m_EngineSettings.GetData(EngineSettings::gameResolutionX.data(), m_ResolutionWidth);
	m_EngineSettings.GetData(EngineSettings::gameResolutionY.data(), m_ResolutionHeight);
	int w, h;
	m_EngineSettings.GetData(EngineSettings::gameWindowSizeX.data(), w);
	m_EngineSettings.GetData(EngineSettings::gameWindowSizeY.data(), h);
	bool maximizeWindow{};
	m_EngineSettings.GetData(EngineSettings::gameWindowMaximized.data(), maximizeWindow);
	bool fullscreen{};
	m_EngineSettings.GetData(EngineSettings::gameFullscreen.data(), fullscreen);

	//// PHYSICS
	m_EngineSettings.GetData(EngineSettings::fixedUpdateInterval.data(), m_FixedUpdateInterval);
	m_EngineSettings.GetData(EngineSettings::maxFixedUpdatesPerFrame.data(), m_MaxFixedUpdatesPerFrame);

	//// OTHER
	m_EngineSettings.GetData(EngineSettings::resourcePath.data(), m_ResourcesPath);

	// Use OpenGL 3.11
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 11);

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
	RESOURCEMANAGER.Init(m_ResourcesPath);
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
	
	// Initialize Timer
	timer.SetFixedTime(m_FixedUpdateInterval);
	float fixedUpdateTimer = 0.0f;
	bool isRunning = true;

	while (isRunning)
	{
		// Add, Remove, Enable, Disable ...
		sceneManager.ChangeSceneGraph();

		// Time Calculations
		const auto startTime = std::chrono::high_resolution_clock::now();
		timer.CalculateTime();
		fixedUpdateTimer += Time::DeltaTime();

		// Update
		isRunning = input.ProcessInput();
		sceneManager.Update();

		// Fixed Update
		int currFrame = 0;
		while (fixedUpdateTimer >= m_FixedUpdateInterval && currFrame <= m_MaxFixedUpdatesPerFrame)
		{
			sceneManager.FixedUpdate();
			fixedUpdateTimer -= m_FixedUpdateInterval;
			currFrame++;
		}

		// Render
		renderer.Render();

		// Wait for next frame
		const auto sleepTime = startTime + std::chrono::milliseconds(16) - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleepTime);
	}

	Cleanup();
}

const Dictionary& Engine::GetSettings() const
{
	return m_EngineSettings;
}

void Engine::InitializeSettings()
{
	// Insert default values
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

	m_EngineSettings.Insert(EngineSettings::fixedUpdateInterval.data(), std::string("0.16f"));
	m_EngineSettings.Insert(EngineSettings::maxFixedUpdatesPerFrame.data(), std::string("50"));

	// Load the engineconfig.ini file
	Logger::LogInfo("[Engine] Loading Engine Settings...");
	auto fstream = std::ifstream(EngineSettings::engineConfig.data());

	// If None, Create engineconfig.ini file
	if (!fstream.is_open())
	{

		Logger::LogWarning("[Engine] No Engine Settings Found. Creating New File...");

		FileIO settingsFile{ EngineSettings::engineConfig.data(), false, false };

		settingsFile.WriteLine("-------------------------");
		settingsFile.WriteLine("WINDOW");
		settingsFile.WriteLine("-------------------------");
		settingsFile.WriteLine("GameResolutionWidth 1280");
		settingsFile.WriteLine("GameResolutionHeight 720");
		settingsFile.WriteLine("GameWindowSizeWidth 1280");
		settingsFile.WriteLine("GameWindowSizeHeight 720");
		settingsFile.WriteLine("GameWindowMaximized 0");
		settingsFile.WriteLine("GameFullscreen 0");
		settingsFile.WriteLine("GameTitle PeakAEngine");
		settingsFile.WriteLine("");

		settingsFile.WriteLine("-------------------------");
		settingsFile.WriteLine("PHYSICS");
		settingsFile.WriteLine("-------------------------");
		settingsFile.WriteLine("FixedUpdateInterval 0.16f");
		settingsFile.WriteLine("MaxFixedUpdatesPerFrame 50");
		settingsFile.WriteLine("");

		settingsFile.WriteLine("-------------------------");
		settingsFile.WriteLine("OTHER");
		settingsFile.WriteLine("-------------------------");
		settingsFile.WriteLine("StartScene 0");
		settingsFile.WriteLine("RendererLayers 3");
		settingsFile.WriteLine("ResourcesPath Resources/");
		settingsFile.WriteLine("");

		fstream = std::ifstream(EngineSettings::engineConfig.data());
	}

	// Load Settings
	std::string line;
	while (fstream)
	{
		std::getline(fstream, line);
		auto sstream = std::stringstream(line);
		{
			m_EngineSettings.StreamChange(sstream);
		}
	}
	Logger::LogSuccess("[Engine] Loaded Engine Settings...");
}

#pragma once
#include "Dictionary.h"
#include "Singleton.h"

#define ENGINE Engine::GetInstance()

struct SDL_Window;

class Engine final : public Singleton<Engine>
{
	friend class Singleton<Engine>;

public:
	void Initialize();
	void Cleanup();
	void Run();

	// Mutators
	const Dictionary& GetSettings() const;

private:
	// Local Functions
	void InitializeSettings();

private:

	SDL_Window* m_Window{};

	int m_ResolutionWidth = 1920;
	int m_ResolutionHeight = 1080;

	Dictionary m_EngineSettings;
};

namespace EngineSettings
{
	inline std::string_view engineConfig{ "engineconfig.ini" };

	inline std::string_view gameResolutionX{ "GameResolutionWidth" };
	inline std::string_view gameResolutionY{ "GameResolutionHeight" };
	inline std::string_view gameWindowSizeX{ "GameWindowSizeWidth" };
	inline std::string_view gameWindowSizeY{ "GameWindowSizeHeight" };
	inline std::string_view gameWindowMaximized{ "GameWindowMaximized" };
	inline std::string_view gameFullscreen{ "GameFullscreen" };
	inline std::string_view renderLayers{ "RenderLayers" };
	inline std::string_view resourcePath{ "ResourcesPath" };
	inline std::string_view gameTitle{ "GameTitle" };
	inline std::string_view gameStartScene{ "StartScene" };
}


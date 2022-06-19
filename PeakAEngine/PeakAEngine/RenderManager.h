#pragma once
#include <SDL.h>
#include <mutex>
#include <functional>

#include "Singleton.h"
#include "RenderTarget.h"


#define RENDERER RenderManager::GetInstance()

class RenderManager final : public Singleton<RenderManager>
{
	friend class Singleton<RenderManager>;

public:
	void Init(SDL_Window* window);
	void Render();
	void Destroy();

private:

	SDL_Window* m_Window{};
	SDL_GLContext m_pContext{};
	std::vector<std::shared_ptr<RenderTarget>> m_RenderLayers;
	std::vector<std::function<void()>> m_PostDrawGLCalls;
	std::mutex m_OpenGlLock;
	int m_WindowResWidth{};
	int m_WindowResHeight{};
	int m_GameResWidth{};
	int m_GameResHeight{};
};


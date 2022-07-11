#pragma once
#include <SDL.h>
#include <mutex>
#include <functional>

#include "Singleton.h"
#include "RenderTarget.h"


#define RENDERER RenderManager::GetInstance()

class Texture2D;



class RenderManager final : public Singleton<RenderManager>
{
	friend class Singleton<RenderManager>;

public:
	void Init(SDL_Window* window);
	void Render();
	void Destroy();

	void RenderTexture(const std::shared_ptr<Texture2D>& texture, const glm::vec2& pos, const glm::vec2& scale, float rotation,
		const glm::vec2& pivot, const SDL_FRect* srcRect, int renderTarget);

private:
	void ActuallyRenderTexture(GLuint glId, int w, int h, const glm::vec2& pos, const glm::vec2& scale, float rotation,
		const glm::vec2& pivot, const SDL_FRect* srcRect) const;

	struct RenderCommand
	{
		std::function<void()> Command;
		int Layer;
	};

	SDL_Window* m_Window{};
	SDL_GLContext m_pContext{};

	std::vector<RenderCommand> m_RenderCommands;

	std::mutex m_OpenGlLock;
	int m_WindowResWidth{};
	int m_WindowResHeight{};
	int m_GameResWidth{};
	int m_GameResHeight{};
};


#pragma once
#include <SDL.h>
#include <mutex>
#include <functional>

#include "Singleton.h"
#include "RenderTarget.h"

#define RENDERER RenderManager::GetInstance()

class Texture2D;
class CameraComponent;

class RenderManager final : public Singleton<RenderManager>
{
	friend class Singleton<RenderManager>;

public:
	void Init(SDL_Window* window);
	void Render();
	void Destroy();

	void SetCamera(CameraComponent* pCamera) { m_pCamera = pCamera; }

	void RenderTexture(const std::shared_ptr<Texture2D>& texture, const glm::vec2& pos, const glm::vec2& scale, float rotation,
		const glm::vec2& pivot, const SDL_FRect& srcRect, int renderTarget);

	// DebugRendering
	void RenderDebugRect(const SDL_FRect& rect, bool filled, const SDL_Color& pColor, float rotation = 0);
	void RenderDebugPolygon(const glm::vec2* points, size_t size, bool filled, const SDL_Color& color);

	glm::vec2 GetWindowSize() const { return {m_GameResWidth, m_GameResHeight}; }

	int GetPixelsPerUnit() const { return m_PixelsPerUnit; }
private:
	void ActuallyRenderTexture(GLuint glId, int w, int h, const glm::vec2& pos, const glm::vec2& scale, float rotation,
		const glm::vec2& pivot, int pixelsPerUnit, const SDL_FRect& srcRect = {-1,-1,-1,-1}) const;
	void ActuallyRenderDebugRect(const SDL_FRect& rect, bool filled, const SDL_Color& pColor, float rotation) const;
	void ActuallyRenderDebugPolygon(const glm::vec2* points, size_t size, bool filled, const SDL_Color& color) const;

	void SetColor(const SDL_Color& color) const;

	struct RenderCommand
	{
		std::function<void()> Command;
		int Layer;
	};

	SDL_Window* m_Window{};
	SDL_GLContext m_pContext{};

	std::vector<RenderCommand> m_RenderCommands;
	std::vector<RenderCommand> m_DebugRenderCommands;

	std::mutex m_OpenGlLock;
	int m_WindowResWidth{};
	int m_WindowResHeight{};
	int m_GameResWidth{};
	int m_GameResHeight{};

	CameraComponent* m_pCamera{ nullptr };

	int m_PixelsPerUnit{ 10 };
};


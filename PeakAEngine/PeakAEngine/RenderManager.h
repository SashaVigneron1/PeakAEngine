#pragma once
#include <SDL.h>
#include <mutex>
#include <functional>

#include "Manager.h"
#include <gl/glew.h>

class Texture2D;
class CameraComponent;

class RenderManager final : public Manager
{
public:
	void Init(SDL_Window* window);
	void Render();
	void Destroy();

	// TextureRendering
	void RenderTexture_Units(const std::shared_ptr<Texture2D>& texture, const glm::vec2& pos, const glm::vec2& scale, float rotation,
		const glm::vec2& pivot, const SDL_FRect& srcRect, int renderTarget);
	void RenderTexture_Pixels(const std::shared_ptr<Texture2D>& texture, const glm::vec2& pos, const glm::vec2& scale, float rotation);

	// DebugRendering
	void RenderDebugRect(const SDL_FRect& rect, bool filled, const SDL_Color& pColor, float rotation = 0);
	void RenderDebugPolygon(const glm::vec2* points, size_t size, bool filled, const SDL_Color& color);
	void RenderDebugGrid() const;

	// Accessor & Mutator Functions
	glm::vec2 GetWindowSize() const { return {m_GameResWidth, m_GameResHeight}; }
	int GetPixelsPerUnit() const { return m_PixelsPerUnit; }
	void SetCamera(CameraComponent* pCamera) { m_pCamera = pCamera; }
	CameraComponent* GetCamera() const { return m_pCamera; }

private:
	// Textures
	void ActuallyRenderTexture(GLuint glId, int w, int h, const glm::vec2& pos, const glm::vec2& scale, float rotation,
		const glm::vec2& pivot, int pixelsPerUnit, const SDL_FRect& srcRect = {-1,-1,-1,-1}) const;
	void ActuallyRenderUITexture(const std::shared_ptr<Texture2D>& texture, const glm::vec2& pos, const glm::vec2& scale, float rotation) const;

	// DebugShapes
	void ActuallyRenderDebugRect(const SDL_FRect& rect, bool filled, const SDL_Color& pColor, float rotation) const;
	void ActuallyRenderDebugPolygon(const glm::vec2* points, size_t size, bool filled, const SDL_Color& color) const;
	void ActuallyRenderDebugLine(const glm::vec2& begin, const glm::vec2& end, float thickness, const SDL_Color& color) const;

	// Accessor & Mutator Functions
	void SetColor(const SDL_Color& color) const;

	// Structs
	struct RenderCommand
	{
		std::function<void()> Command;
		int Layer;
	};

	// SDL GL Variables
	SDL_Window* m_Window{};
	SDL_GLContext m_pContext{};

	// Render Commands
	std::vector<RenderCommand> m_RenderCommands;
	std::vector<RenderCommand> m_DebugRenderCommands;
	std::vector<RenderCommand> m_UIRenderCommands;

	// Window Information
	std::mutex m_OpenGlLock;
	int m_WindowResWidth{};
	int m_WindowResHeight{};
	int m_GameResWidth{};
	int m_GameResHeight{};

	// Debug Grid
	const bool m_ShouldRenderDebugGrid{ true };
	const float m_GridLineThickness{ 2.f };
	const SDL_Color m_GridColor{ 255,255,255,100 };

	// Other
	CameraComponent* m_pCamera{ nullptr };
	int m_PixelsPerUnit{ 10 };
};


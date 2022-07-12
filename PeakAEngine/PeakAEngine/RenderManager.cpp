#include "PeakAEnginePCH.h"
#include "RenderManager.h"

#include <gl/glew.h>
#include <gl/wglew.h>

#include "PeakAEngine.h"
#include "ResourceManager.h"
#include "Texture2D.h"

#include "SceneManager.h"

#include "GUIManager.h"

#include "GameObject.h"
#include "Transform.h"
#include "CameraComponent.h"

void RenderManager::Init(SDL_Window* window)
{
	auto& settings = ENGINE.GetSettings();

	settings.GetData(EngineSettings::gameResolutionX.data(), m_GameResWidth);
	settings.GetData(EngineSettings::gameResolutionY.data(), m_GameResHeight);
	settings.GetData(EngineSettings::rendererPixelsPerUnit.data(), m_PixelsPerUnit);

	m_Window = window;

	/*
	** OPENGL
	*/

	// Create OpenGL context 
	m_pContext = SDL_GL_CreateContext(window);
	if (m_pContext == nullptr)
	{
		Logger::LogError("[RenderManager] Error When Calling SDL_GL_CreateContext: " + std::string{ SDL_GetError() });
		return;
	}

	if (glewInit() != GLEW_OK)
	{
		Logger::LogError("[RenderManager] Failed To Initialize GLEW: " + std::string{ SDL_GetError() });
	}

	// Set the swap interval for the current OpenGL context,
	// synchronize it with the vertical retrace
	//if (window.isVSyncOn)
	{
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			Logger::LogError("[RenderManager] Error When Calling SDL_GL_SetSwapInterval: " + std::string{ SDL_GetError() });
			return;
		}
	}
	//else
	{
		//SDL_GL_SetSwapInterval(0);
	}

	SDL_GL_GetDrawableSize(window, &m_WindowResWidth, &m_WindowResHeight);

	// Set the Projection matrix to the identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up a two-dimensional orthographic viewing region.
	gluOrtho2D(0, m_GameResWidth, 0, m_GameResHeight); // y from bottom to top

	// Set the viewport to the client window area
	// The viewport is the rectangular region of the window where the image is drawn.
	glViewport(0, 0, m_GameResWidth, m_GameResHeight);

	// Set the Modelview matrix to the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable color blending and use alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// INITIALIZE GUI
	GUI.Initialize(window);
}

void RenderManager::Render()
{
	// Clear Color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	// Sort According To Layer
	std::stable_sort(
		m_RenderCommands.begin(), m_RenderCommands.end(),
		[](const RenderCommand& a, const RenderCommand& b)
		{
			return a.Layer < b.Layer;
		});

	// Render Logic
	glPushMatrix();
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// First translate [0, 0] to the center of the screen
		glTranslatef((float)m_GameResWidth / 2.f, (float)m_GameResHeight / 2.f, 0.0f);

		// Translate To Camera Pos
		if (m_pCamera)
		{
			auto camScale = m_pCamera->GetGameObject()->GetTransform()->GetWorldScale();
			glScalef(camScale.x, camScale.y, 1);

			auto camPos = m_pCamera->GetGameObject()->GetTransform()->GetWorldPosition();
			camPos /= m_PixelsPerUnit;
			glTranslatef(-camPos.x, -camPos.y, 0.0f);
		}

		// Create Render Commands
		SCENEMANAGER.Render();

		// Execute Render Commands
		for (auto& renderCommand : m_RenderCommands)
			renderCommand.Command();
		m_RenderCommands.clear();

		// Create DebugRender Commands
		SCENEMANAGER.RenderGizmos();

		// Execute Debug Render Commands
		for (auto& renderCommand : m_DebugRenderCommands)
			renderCommand.Command();
		m_DebugRenderCommands.clear();
	}
	glPopMatrix();

	// GUI Logic
	GUI.StartFrame();
	SCENEMANAGER.DrawImGui();
	GUI.Render();

	// Present
	SDL_GL_SwapWindow(m_Window);
}

void RenderManager::Destroy()
{
	SDL_GL_DeleteContext(m_pContext);
	GUI.Destroy();
}

void RenderManager::RenderTexture(const std::shared_ptr<Texture2D>& texture, const glm::vec2& pos, const glm::vec2& scale, float rotation, const glm::vec2& pivot, const SDL_FRect& srcRect, int renderTarget)
{
	m_RenderCommands.push_back(
		{
			[=]()
			{
				ActuallyRenderTexture(texture->GetId(), texture->GetWidth(), texture->GetHeight(), pos, scale, rotation, pivot, texture.get()->GetPixelsPerUnit(), srcRect);
			},
			renderTarget
		}
	);
}

void RenderManager::ActuallyRenderTexture(GLuint glId, int w, int h, const glm::vec2& pos, const glm::vec2& scale, float rotation,
	const glm::vec2& pivot, int pixelsPerUnit, const SDL_FRect& srcRect) const
{
	{
		const glm::vec2 invertedYPos{ pos.x, pos.y };

		float width = srcRect.w;
		float height = srcRect.h;
		if (srcRect.w < 0) 
		{
			width = float(w);
			height = float(h);
		}

		glm::vec2 vertices[4]{};

		// Vertex coordinates for centered orientation
		float vertexLeft{ (1.f - pivot.x) - 1.f };
		float vertexBottom{ (1.f - pivot.y) - 1.f };
		float vertexRight{ 1.f - pivot.x };
		float vertexTop{ 1.f - pivot.y };

		vertexLeft *= width * scale.x / pixelsPerUnit;
		vertexRight *= width * scale.x / pixelsPerUnit;
		vertexTop *= height * scale.y / pixelsPerUnit;
		vertexBottom *= height * scale.y / pixelsPerUnit;

		constexpr float inverse180{ 1.f / 180.f * float(M_PI) };

		float cosAngle = cos(rotation * inverse180);
		float sinAngle = sin(rotation * inverse180);

		vertices[0] = { vertexLeft * cosAngle - vertexBottom * sinAngle, vertexBottom * cosAngle + vertexLeft * sinAngle };
		vertices[1] = { vertexLeft * cosAngle - vertexTop * sinAngle, vertexTop * cosAngle + vertexLeft * sinAngle };
		vertices[2] = { vertexRight * cosAngle - vertexTop * sinAngle, vertexTop * cosAngle + vertexRight * sinAngle };
		vertices[3] = { vertexRight * cosAngle - vertexBottom * sinAngle, vertexBottom * cosAngle + vertexRight * sinAngle };

		vertices[0] += invertedYPos;
		vertices[1] += invertedYPos;
		vertices[2] += invertedYPos;
		vertices[3] += invertedYPos;

		vertices[0] *= m_PixelsPerUnit;
		vertices[1] *= m_PixelsPerUnit;
		vertices[2] *= m_PixelsPerUnit;
		vertices[3] *= m_PixelsPerUnit;

		// Texture coordinates
		float textLeft{ 0 };
		float textRight{ 1 };
		float textBottom{ 1 };
		float textTop{ 0 };

		if (srcRect.w > 0)
		{
			textLeft = srcRect.x / w;
			textRight = (srcRect.x + srcRect.w) / w;
			textTop = (srcRect.y) / h;
			textBottom = (srcRect.y + srcRect.h) / h;
		}


		// Tell opengl which texture we will use
		glBindTexture(GL_TEXTURE_2D, glId);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		// Draw
		glEnable(GL_TEXTURE_2D);
		{
			glBegin(GL_QUADS);
			{
				glTexCoord2f(textLeft, textBottom);
				glVertex2f(vertices[0].x, vertices[0].y);

				glTexCoord2f(textLeft, textTop);
				glVertex2f(vertices[1].x, vertices[1].y);

				glTexCoord2f(textRight, textTop);
				glVertex2f(vertices[2].x, vertices[2].y);

				glTexCoord2f(textRight, textBottom);
				glVertex2f(vertices[3].x, vertices[3].y);
			}
			glEnd();
		}
		glDisable(GL_TEXTURE_2D);
	}

	//SetRenderTargetScreen();
}



void RenderManager::SetColor(const SDL_Color& color)
{
	glColor4ub(color.r, color.g, color.b, color.a);
}

void RenderManager::RenderDebugRect(const SDL_FRect& rect, bool filled, const SDL_Color& pColor)
{
	m_DebugRenderCommands.push_back(
		{
			[=]()
			{
				ActuallyRenderDebugRect(rect, filled, pColor);
			},
			1
		}
	);
}

void RenderManager::ActuallyRenderDebugRect(const SDL_FRect& rect, bool filled, const SDL_Color& pColor)
{
	SetColor(pColor);

	SDL_FRect newRect{ rect.x * m_PixelsPerUnit,
	rect.y * m_PixelsPerUnit,
	rect.w * m_PixelsPerUnit,
	rect.h * m_PixelsPerUnit };

	glBegin(filled ? GL_POLYGON : GL_LINE_LOOP);
	glVertex2f(newRect.x, newRect.y);
	glVertex2f(newRect.x + newRect.w, newRect.y);
	glVertex2f(newRect.x + newRect.w, newRect.y + newRect.h);
	glVertex2f(newRect.x, newRect.y + newRect.h);
	glEnd();
}
#include "PeakAEnginePCH.h"
#include "RenderManager.h"

#include <gl/glew.h>
#include <gl/wglew.h>

#include "PeakAEngine.h"
#include "ResourceManager.h"

void RenderManager::Init(SDL_Window* window)
{
	auto& settings = ENGINE.GetSettings();

	settings.GetData(EngineSettings::gameResolutionX.data(), m_GameResWidth);
	settings.GetData(EngineSettings::gameResolutionY.data(), m_GameResHeight);

	m_Window = window;

	/*
	** OPENGL
	*/

	// Create OpenGL context 
	m_pContext = SDL_GL_CreateContext(window);
	if (m_pContext == nullptr)
	{
		std::cerr << "Core::Initialize( ), error when calling SDL_GL_CreateContext: " << SDL_GetError() << std::endl;
		return;
	}

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW " << SDL_GetError() << std::endl;
	}

	// Set the swap interval for the current OpenGL context,
	// synchronize it with the vertical retrace
	//if (window.isVSyncOn)
	{
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			std::cerr << "Core::Initialize( ), error when calling SDL_GL_SetSwapInterval: " << SDL_GetError() << std::endl;
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

	int renderLayers{};
	settings.GetData(EngineSettings::renderLayers.data(), renderLayers);
	m_RenderLayers.reserve(renderLayers);
	for (int i{}; i < renderLayers; ++i)
	{
		m_RenderLayers.emplace_back(RESOURCEMANAGER.CreateRenderTexture(m_GameResWidth, m_GameResHeight));
	}
}

void RenderManager::Render()
{
	// Clear Color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto& renderTarget : m_RenderLayers)
	{
		glClearColor(0, 0, 0, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, renderTarget->GetFrameBuffer());
		glClear(GL_COLOR_BUFFER_BIT);
	}

	// Render Logic

	// Present
	SDL_GL_SwapWindow(m_Window);
}

void RenderManager::Destroy()
{
	SDL_GL_DeleteContext(m_pContext);
}

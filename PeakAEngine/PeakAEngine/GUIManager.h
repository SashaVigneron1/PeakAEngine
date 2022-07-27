#pragma once

#include "Manager.h"
#include <SDL.h>


class GUIManager final : public Manager
{
public:

	void Initialize(SDL_Window* pWindow);
	void Destroy();

	void StartFrame();
	void Render();

	void HandleInput(const SDL_Event* e);

private:
	void SetStyle();

	SDL_Window* m_pWindow = nullptr;

};


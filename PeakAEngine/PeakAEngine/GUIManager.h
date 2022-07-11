#pragma once

#include "Singleton.h"

#define GUI GUIManager::GetInstance()


class GUIManager final : public Singleton<GUIManager>
{
	friend class Singleton<GUIManager>;

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


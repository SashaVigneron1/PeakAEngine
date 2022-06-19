#pragma once

#include "Singleton.h"
#include "SDL.h"

#define RESOURCEMANAGER ResourceManager::GetInstance()

class RenderTarget;
class Texture2D;

class ResourceManager final : public Singleton<ResourceManager>
{

	friend class Singleton<ResourceManager>;

public:
	void Init(const std::string& dataFilePath);

	std::shared_ptr<RenderTarget> CreateRenderTexture(int width, int height);
	std::shared_ptr<Texture2D> LoadTexture(const std::string& file);
	std::shared_ptr<Texture2D> LoadTexture(SDL_Surface* pSurface);

private:
	std::string m_DataPath;
	std::map<std::string, std::shared_ptr<Texture2D>> m_Textures;
};
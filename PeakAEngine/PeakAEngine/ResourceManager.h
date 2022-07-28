#pragma once

#include "Manager.h"
#include "SDL.h"

class RenderTarget;
class Texture2D;
class Font;

class ResourceManager final : public Manager
{
public:
	void Init(const std::string& dataFilePath);

	std::shared_ptr<Texture2D> LoadTexture(const std::string& filePath);
	std::shared_ptr<Texture2D> LoadTexture(SDL_Surface* pSurface);
	
	std::shared_ptr<Font> LoadFont(const std::string& fontPath, unsigned int size);

private:
	std::string m_DataPath;
	std::map<std::string, std::shared_ptr<Texture2D>> m_Textures;
	std::map<std::string, std::shared_ptr<Font>> m_Fonts;
};
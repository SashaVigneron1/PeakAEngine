#include "PeakAEnginePCH.h"
#include "ResourceManager.h"

#include "gl/glew.h"

#include <SDL_image.h>

#include "RenderManager.h"
#include "Texture2D.h"

#include "Font.h"
#include <SDL_ttf.h>

void ResourceManager::Init(const std::string& dataFilePath)
{
	m_DataPath = dataFilePath;

	if (TTF_Init() != 0)
	{
		Logger::LogError("[ResourceManager] Failed to load support for fonts: " + std::string{ SDL_GetError() });
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}



std::shared_ptr<Texture2D> ResourceManager::LoadTexture(const std::string& file)
{
	if (!m_Textures.contains(file))
	{
		Logger::LogInfo("[ResourceManager] Loading Texture: " + file);

		const auto fullPath = m_DataPath + file;
		auto texture = IMG_Load(fullPath.c_str());
		if (texture == nullptr)
		{
			Logger::LogError("[ResourceManager] Failed to load texture: " + std::string{ SDL_GetError() });
			throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
		}

		m_Textures[file] = LoadTexture(texture);
		Logger::LogSuccess("[ResourceManager] Texture Succesfully Loaded: " + file);
	}

	std::shared_ptr<Texture2D> texture = m_Textures[file];
	return texture;
}

std::shared_ptr<Texture2D> ResourceManager::LoadTexture(SDL_Surface* pSurface)
{
	// Get Image Size
	const int width = pSurface->w;
	const int height = pSurface->h;
	GLuint id;

	// Get Pixel Format
	GLenum pixelFormat{ GL_RGB };
	switch (pSurface->format->BytesPerPixel)
	{
	case 3:
		if (pSurface->format->Rmask == 0x000000ff)
			pixelFormat = GL_RGB;
		else
			pixelFormat = GL_BGR_EXT;
		break;
	case 4:
		if (pSurface->format->Rmask == 0x000000ff)
			pixelFormat = GL_RGBA;
		else
			pixelFormat = GL_BGRA_EXT;
		break;
	default:
		throw std::runtime_error("Texture::CreateFromSurface, unknown pixel format");
	}

	//Generate an array of textures.  We only want one texture (one element array), so trick
	//it by treating "texture" as array of length one.
	glGenTextures(1, &id);

	// Select(bind) the texture we just generated as the current 2D texture OpenGL is using / modifying.
	//All subsequent changes to OpenGL's texturing state for 2D textures will affect this texture.
	glBindTexture(GL_TEXTURE_2D, id);
	// check for errors. Can happen if a texture is created while a static pointer is being initialized, even before the call to the main function.
	GLenum e = glGetError();
	if (e != GL_NO_ERROR)
	{
		/*std::cerr << "Texture::CreateFromSurface, error binding textures, Error id = " << e << '\n';
		std::cerr << "Can happen if a texture is created before performing the initialization code (e.g. a static Texture object).\n";
		std::cerr << "There might be a white rectangle instead of the image.\n";*/
	}

	// Specify the texture's data.  
	// This function is a bit tricky, and it's hard to find helpful documentation. 
	// A summary:
	//    GL_TEXTURE_2D:    The currently bound 2D texture (i.e. the one we just made)
	//                0:    The mipmap level.  0, since we want to update the base level mipmap image (i.e., the image itself,
	//                         not cached smaller copies)
	//          GL_RGBA:    Specifies the number of color components in the texture.
	//                     This is how OpenGL will store the texture internally (kinda)--
	//                     It's essentially the texture's type.
	//       surface->w:    The width of the texture
	//       surface->h:    The height of the texture
	//                0:    The border.  Don't worry about this if you're just starting.
	//      pixelFormat:    The format that the *data* is in--NOT the texture! 
	// GL_UNSIGNED_BYTE:    The type the data is in.  In SDL, the data is stored as an array of bytes, with each channel
	//                         getting one byte.  This is fairly typical--it means that the image can store, for each channel,
	//                         any value that fits in one byte (so 0 through 255).  These values are to be interpreted as
	//                         *unsigned* values (since 0x00 should be dark and 0xFF should be bright).
	//  surface->pixels:    The actual data.  As above, SDL's array of bytes.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pSurface->w, pSurface->h, 0, pixelFormat, GL_UNSIGNED_BYTE, pSurface->pixels);

	// Set the minification and magnification filters.  In this case, when the texture is minified (i.e., the texture's pixels (texels) are
	// *smaller* than the screen pixels you're seeing them on, linearly filter them (i.e. blend them together).  This blends four texels for
	// each sample--which is not very much.  Mipmapping can give better results.  Find a texturing tutorial that discusses these issues
	// further.  Conversely, when the texture is magnified (i.e., the texture's texels are *larger* than the screen pixels you're seeing
	// them on), linearly filter them.  Qualitatively, this causes "blown up" (overmagnified) textures to look blurry instead of blocky.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return std::make_shared<Texture2D>(id, width, height);
}

std::shared_ptr<Font> ResourceManager::LoadFont(const std::string& fontPath, unsigned int size)
{
	if (!m_Fonts.contains(fontPath))
	{
		Logger::LogInfo("[ResourceManager] Loading Font: " + fontPath);

		m_Fonts[fontPath] = std::make_shared<Font>(m_DataPath + fontPath, size);
	}

	std::shared_ptr<Font> font = m_Fonts[fontPath];
	return font;
}

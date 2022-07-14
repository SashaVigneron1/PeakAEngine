#pragma once
#include <gl/glew.h>
#include <filesystem>

class Texture2D final
{
	friend class RenderManager;
	friend class ResourceManager;

public:
	Texture2D() = default;

	Texture2D(const Texture2D&) = delete;
	Texture2D& operator=(const Texture2D&) = delete;

	Texture2D(Texture2D&& other) noexcept
		: m_Id{ other.m_Id }
		, m_Width{ other.m_Width }
		, m_Height{ other.m_Height }
		, m_sourceFile{ std::move(other.m_sourceFile) }
	{
		other.m_Id = 0;
		other.m_Height = 0;
		other.m_Width = 0;
	}

	Texture2D& operator=(Texture2D&& other) noexcept
	{
		m_Id = other.m_Id;
		other.m_Id = 0;
		m_Width = other.m_Width;
		other.m_Width = 0;
		m_Height = other.m_Height;
		other.m_Height = 0;
		m_sourceFile = std::move(other.m_sourceFile);
		return *this;
	}

	explicit Texture2D(GLuint id, int width, int height)
		: m_Id{ id }, m_Width{ width }, m_Height{ height }{}

	Texture2D(SDL_Surface* pSurface, int width, int height)
		: m_Width{ width }, m_Height{ height } 
	{
		// Get pixel format information and translate to OpenGl format
		GLenum pixelFormat{ GL_RGB };
		switch (pSurface->format->BytesPerPixel)
		{
		case 3:
		{
			if (pSurface->format->Rmask == 0x000000ff)
			{
				pixelFormat = GL_RGB;
			}
			else
			{
				pixelFormat = GL_BGR;
			}
			break;
		}
		case 4:
		{
			if (pSurface->format->Rmask == 0x000000ff)
			{
				pixelFormat = GL_RGBA;
			}
			else
			{
				pixelFormat = GL_BGRA;
			}
			break;
		}
		default:
		{
			Logger::LogError("[Texture2D] Error creating texture: unknow pixel format, BytesPerPixel: " + std::to_string((int)pSurface->format->BytesPerPixel) + ". Use 32 bit or 24 bit images.");
			return;
		}
		}

		// Generate id
		glGenTextures(1, &m_Id);

		// Set texture as the one we're working with
		glBindTexture(GL_TEXTURE_2D, m_Id);

		// check for errors. Can happen if a texture is created while a static pointer is being initialized, even before the call to the main function.
		GLenum e = glGetError();
		if (e != GL_NO_ERROR)
		{
			Logger::LogError("[Texture2D] Texture::CreateFromSurface, error binding textures, Error id = " + std::to_string(e));
			Logger::LogError("[Texture2D] Can happen if a texture is created before performing the initialization code (e.g. a static Texture object).");
			Logger::LogError("[Texture2D] There might be a white rectangle instead of the image.");
		}

		// Copy data from SDL surface to OpenGL texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pSurface->w, pSurface->h, 0, pixelFormat, GL_UNSIGNED_BYTE, pSurface->pixels);

		// Texture does not repeat
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Use nearest neighbour interpolation
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	~Texture2D() { glDeleteTextures(1, &m_Id); }

	GLuint GetId() const { return m_Id; }
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }

	const std::filesystem::path& GetFilePath() const { return m_sourceFile; }

	inline bool IsValid() { return m_Id; }
	inline operator bool() { return IsValid(); }

	void SetPixelsPerUnit(int value) { m_PixelsPerUnit = value; }
	int GetPixelsPerUnit() const { return m_PixelsPerUnit; }
private:
	GLuint m_Id{};
	int m_Width{};
	int m_Height{};

	int m_PixelsPerUnit{ 1 };

	std::filesystem::path m_sourceFile{};
};
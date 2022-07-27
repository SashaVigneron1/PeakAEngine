#pragma once

#include "SDL_mixer.h"
#include "Logger.h"
#include <string>

class AudioClip final
{
public:
	AudioClip(const std::string& filepath, bool dontDestroyOnLoad = false, int loops = 0)
		: m_FilePath{ filepath }
		, m_Loops{ loops }
		, m_DontDestroyOnLoad{ dontDestroyOnLoad }
	{
		m_pChunk = Mix_LoadWAV(m_FilePath.c_str());
		if (m_pChunk == nullptr)
		{
			Logger::LogError("[AudioClip] Something went wrong trying to load file: ", Mix_GetError());
		}
	}

	~AudioClip()
	{
		if (m_pChunk)
			Mix_FreeChunk(m_pChunk);
	}

	AudioClip(const AudioClip& other) = delete;
	AudioClip(AudioClip&& other) noexcept = delete;
	AudioClip& operator=(const AudioClip& other) = delete;
	AudioClip& operator=(AudioClip&& other) noexcept = delete;

	void Play()
	{
		if (m_pChunk)
			m_Channel = Mix_PlayChannel(-1, m_pChunk, m_Loops);
	}
	void Stop() 
	{
		if (m_pChunk && m_Channel >= 0)
			Mix_HaltChannel(m_Channel);
	}
	void SetVolume(int volume)
	{
		if (m_pChunk)
			Mix_VolumeChunk(m_pChunk, volume);
	}
	int GetVolume() const
	{
		// If less than 0 then chunk volume will not be set
		if (m_pChunk)
			return Mix_VolumeChunk(m_pChunk, -1);
		return 0;
	}
	void SetDontDestroyOnLoad(bool value) { m_DontDestroyOnLoad = value; }
	bool IsDontDestroyOnLoad() const { return m_DontDestroyOnLoad; }
private:
	std::string m_FilePath;
	Mix_Chunk* m_pChunk;
	int m_Channel;
	int m_Loops;
	bool m_DontDestroyOnLoad;
};

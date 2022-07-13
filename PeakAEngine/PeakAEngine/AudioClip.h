#pragma once

struct Mix_Chunk;

class AudioClip final
{
public:
	//ToDo: Move this to resourcemanager
	AudioClip(const std::string& filepath, int loops = 0);
	~AudioClip();

	AudioClip(const AudioClip& other) = delete;
	AudioClip(AudioClip&& other) noexcept = delete;
	AudioClip& operator=(const AudioClip& other) = delete;
	AudioClip& operator=(AudioClip&& other) noexcept = delete;

	void Play();
	void SetVolume(int volume);
	int GetVolume();

private:
	std::string m_FilePath;
	Mix_Chunk* m_pChunk;
	int m_Loops;
};

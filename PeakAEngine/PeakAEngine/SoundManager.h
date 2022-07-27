#pragma once

#include "Manager.h"

class AudioClip;

class SoundSystem
{
public:
	SoundSystem();
	virtual ~SoundSystem() = default;

	SoundSystem(const SoundSystem& other) = delete;
	SoundSystem(SoundSystem&& other) noexcept = delete;
	SoundSystem& operator=(const SoundSystem& other) = delete;
	SoundSystem& operator=(SoundSystem&& other) noexcept = delete;

	virtual void Play(int clipId);
	virtual int AddClip(const std::string& clipFilePath, int loops = 0);

protected:

private:
	class SoundSystemImpl;
	SoundSystemImpl* m_pSoundSystem;
};

class SoundManager final : public Manager
{
public:
	SoundManager() : m_pSoundSystem{ new SoundSystem() } {}
	virtual ~SoundManager() override { delete m_pSoundSystem; }

	SoundManager(const SoundManager& other) = delete;
	SoundManager(SoundManager&& other) noexcept = delete;
	SoundManager& operator=(const SoundManager& other) = delete;
	SoundManager& operator=(SoundManager&& other) noexcept = delete;

	void Play(int clipId)
	{
		Logger::LogInfo("[SoundSystem] Playing Sound: \tId:" + std::to_string(clipId));
		m_pSoundSystem->Play(clipId);
	}
	int AddClip(const std::string& clipFilePath, int loops = 1) 
	{
		Logger::LogInfo("[SoundSystem] Loading Clip...");
		return m_pSoundSystem->AddClip(clipFilePath, loops);
	}

private:
	SoundSystem* m_pSoundSystem{};
};
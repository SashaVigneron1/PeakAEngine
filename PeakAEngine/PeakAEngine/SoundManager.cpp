#include "PeakAEnginePCH.h"
#include "SoundManager.h"

#include <mutex>
#include <queue>
#include <thread>

#include "AudioClip.h"
#include "SDL.h"
#include "SDL_mixer.h"

class SoundManager::SoundSystemImpl
{
public:
	SoundSystemImpl();
	~SoundSystemImpl();

	SoundSystemImpl(const SoundSystemImpl& other) = delete;
	SoundSystemImpl(SoundSystemImpl&& other) noexcept = delete;
	SoundSystemImpl& operator=(const SoundSystemImpl& other) = delete;
	SoundSystemImpl& operator=(SoundSystemImpl&& other) noexcept = delete;

	void Play(int clipId)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		m_SoundsToPlay.push(m_pClips[clipId]);
		m_CV.notify_all();
	}
	int AddClip(const std::string& clipFilePath, int loops = 0)
	{
		m_pClips.push_back(new AudioClip{ clipFilePath, loops });
		return (int)m_pClips.size() - 1;
	}

	void RunEventQueue();

private:
	std::vector<AudioClip*> m_pClips;
	std::queue<AudioClip*> m_SoundsToPlay;

	std::thread m_Thread;
	std::mutex m_Mutex;
	std::condition_variable m_CV;
	std::atomic<bool> m_StopThread;
};

SoundManager::SoundSystemImpl::SoundSystemImpl()
{
	//Mix_Chunk* _sample[2];
	//memset(_sample, 0, sizeof(Mix_Chunk*) * 2);

	int result = Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 512);
	if (result < 0)
	{
		Logger::LogError("[SoundSystem] Unable to open audio: ", SDL_GetError());
		return;
	}

	result = Mix_AllocateChannels(16);
	if (result < 0)
	{
		Logger::LogError("[SoundSystem] Unable to allocate mixing channels: ", SDL_GetError());
		return;
	}

	m_Thread = std::thread(&SoundSystemImpl::RunEventQueue, this);
}

SoundManager::SoundSystemImpl::~SoundSystemImpl()
{
	Mix_CloseAudio();
	m_StopThread.store(true);
	m_CV.notify_all();
	m_Thread.join();
}

void SoundManager::SoundSystemImpl::RunEventQueue()
{
	while (true)
	{
		// Wait for a sound to be played or for the thread to be stopped
		std::unique_lock<std::mutex> lock(m_Mutex);
		m_CV.wait(lock, [&]() { return !m_SoundsToPlay.empty() || m_StopThread.load(); });

		// Check if thread needs to be stopped
		if (m_StopThread.load())
		{
			lock.unlock();
			break;
		}

		// Remove the sound from the queue
		const auto clip = m_SoundsToPlay.front();
		m_SoundsToPlay.pop();

		lock.unlock();

		// Play the sound
		clip->Play();

	}
}


SoundManager::SoundManager()
	: m_pSoundSystem{ new SoundSystemImpl() }
{
}

void SoundManager::Play(int clipId)
{
	m_pSoundSystem->Play(clipId);
}

int SoundManager::AddClip(const std::string& clipFilePath, int loops)
{
	return m_pSoundSystem->AddClip(clipFilePath, loops);
}

#include "PeakAEnginePCH.h"
#include "SoundManager.h"

#include <mutex>
#include <queue>
#include <thread>

#include "AudioClip.h"
#include "SDL.h"
#include "SDL_mixer.h"

class SoundSystem::SoundSystemImpl
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
	int AddClip(const std::string& clipFilePath, bool dontDestroyOnLoad, int loops = 0)
	{
		m_pClips.push_back(std::make_shared<AudioClip>( clipFilePath, dontDestroyOnLoad, loops ));
		return (int)m_pClips.size() - 1;
	}
	void ChangeScene();

	void RunEventQueue();

private:
	std::vector<std::shared_ptr<AudioClip>> m_pClips;
	std::queue<std::shared_ptr<AudioClip>> m_SoundsToPlay;

	std::thread m_Thread;
	std::mutex m_Mutex;
	std::condition_variable m_CV;
	std::atomic<bool> m_StopThread;
};

SoundSystem::SoundSystemImpl::SoundSystemImpl()
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

SoundSystem::SoundSystemImpl::~SoundSystemImpl()
{
	// Clear Current Queue & Delete AudioClips
	while (!m_SoundsToPlay.empty()) m_SoundsToPlay.pop();
	m_pClips.clear();

	Mix_CloseAudio();
	m_StopThread.store(true);
	m_CV.notify_all();
	m_Thread.join();
}

void SoundSystem::SoundSystemImpl::ChangeScene()
{
	// Stop Playing Clips
	for (auto clip : m_pClips)
	{
		if (!clip->IsDontDestroyOnLoad())
		{
			// Stop Clip
			clip->Stop();
		}
	}

	// Clear Current Queue
	while (!m_SoundsToPlay.empty()) m_SoundsToPlay.pop();
}

void SoundSystem::SoundSystemImpl::RunEventQueue()
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


SoundSystem::SoundSystem()
	: m_pSoundSystem{ new SoundSystemImpl() }
{
}

void SoundSystem::Play(int clipId)
{
	m_pSoundSystem->Play(clipId);
}

int SoundSystem::AddClip(const std::string& clipFilePath, bool dontDestroyOnLoad, int loops)
{
	return m_pSoundSystem->AddClip(clipFilePath, dontDestroyOnLoad, loops);
}

void SoundSystem::ChangeScene()
{
	m_pSoundSystem->ChangeScene();
}


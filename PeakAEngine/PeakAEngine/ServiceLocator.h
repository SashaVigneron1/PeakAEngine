#pragma once
#include "SoundManager.h"
#include "Singleton.h"

#define SERVICELOCATOR ServiceLocator::GetInstance()

class ServiceLocator : public Singleton<ServiceLocator>
{
public:
	static SoundManager* GetSoundSystem() { return m_pSoundSystem; }
	static void RegisterSoundSystem(SoundManager* pSoundSystem) { m_pSoundSystem = pSoundSystem == nullptr ? &m_pDefaultSoundSystem : pSoundSystem; }

private:
	static SoundManager* m_pSoundSystem;
	static NULL_SoundSystem m_pDefaultSoundSystem;

	//ToDo: Add Things Like Renderer ETC.
};
NULL_SoundSystem ServiceLocator::m_pDefaultSoundSystem;
SoundManager* ServiceLocator::m_pSoundSystem = &m_pDefaultSoundSystem;


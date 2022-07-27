#pragma once

// Include Managers
#include "GameStateManager.h"
#include "GUIManager.h"
#include "InputManager.h"
#include "NetworkManager.h" 
#include "PlayfabManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "Time.h"
#include "UIManager.h"

#define GAMESTATE Managers::Get<GameStateManager>()
#define GUI Managers::Get<GUIManager>()
#define INPUTMANAGER Managers::Get<InputManager>()
#define NETWORKMANAGER Managers::Get<NetworkManager>()
#define PLAYFABMANAGER Managers::Get<PlayfabManager>()
#define RENDERER Managers::Get<RenderManager>()
#define RESOURCEMANAGER Managers::Get<ResourceManager>()
#define SCENEMANAGER Managers::Get<SceneManager>()
#define SOUNDMANAGER Managers::Get<SoundManager>()
#define TIME Managers::Get<Time>()
#define UI Managers::Get<UIManager>()

class Manager;

class Managers final
{
public:
    Managers()
    {
    }

    static void Initialize()
    {
        m_managersByType[typeid(GameStateManager).name()] = CreateManager<GameStateManager>();
        m_managersByType[typeid(GUIManager).name()] = CreateManager<GUIManager>();
        m_managersByType[typeid(InputManager).name()] = CreateManager<InputManager>();
        m_managersByType[typeid(NetworkManager).name()] = CreateManager<NetworkManager>();
        m_managersByType[typeid(PlayfabManager).name()] = CreateManager<PlayfabManager>();
        m_managersByType[typeid(RenderManager).name()] = CreateManager<RenderManager>();
        m_managersByType[typeid(ResourceManager).name()] = CreateManager<ResourceManager>();
        m_managersByType[typeid(SceneManager).name()] = CreateManager<SceneManager>();
        m_managersByType[typeid(SoundManager).name()] = CreateManager<SoundManager>();
        m_managersByType[typeid(Time).name()] = CreateManager<Time>();
        m_managersByType[typeid(UIManager).name()] = CreateManager<UIManager>();
    }

    template<class T>
    static std::shared_ptr<T> Get()
    {
        return std::static_pointer_cast<T>(m_managersByType[typeid(T).name()]);
    }
private:

    template<typename ManagerType>
    static std::shared_ptr<Manager> CreateManager()
    {
        return std::static_pointer_cast<Manager>(std::make_shared<ManagerType>());
    }

    static std::map<const char*, std::shared_ptr<Manager>> m_managersByType;
};



#include "PeakAEnginePCH.h"
#include "SceneManager.h"

#include "Scene.h"

#include "Managers.h"

void SceneManager::DrawImGui() const
{
	if (m_ActiveScene) m_ActiveScene->DrawImGui();
}

void SceneManager::Update() const
{
	if (m_ActiveScene)
	{
		m_ActiveScene->Update();
		m_ActiveScene->OnHover(INPUTMANAGER->GetMouseState().position);

		if (INPUTMANAGER->GetMouseButtonPressed(MouseButton::LMB))
			m_ActiveScene->OnClick();
	}
}

void SceneManager::FixedUpdate() const
{
	if (m_ActiveScene) m_ActiveScene->FixedUpdate();
}

void SceneManager::Render() const
{
	if (m_ActiveScene) m_ActiveScene->Render();
}

void SceneManager::RenderGizmos() const
{
	if (m_ActiveScene) m_ActiveScene->RenderGizmos();
}

void SceneManager::ChangeSceneGraph()
{
	if (m_ActiveScene) m_ActiveScene->ChangeSceneGraph();
}

SceneManager::~SceneManager()
{
	for (auto scenePair : m_Scenes) 
{
		delete scenePair.second;
	}
}

void SceneManager::AddScene(const std::string& name, Scene* scene)
{
	// Make sure scene doesn't already exist
	assert(m_Scenes.find(name) == m_Scenes.end());

	// Add scene
	scene->SetName(name);
	scene->RootInitialize();
	m_Scenes.insert(std::make_pair(name, scene));

	// If this is the first and only scene, set this active
	if (m_Scenes.size() == 1)
		m_ActiveScene = scene;

	Logger::LogInfo("[SceneManager] Added Scene: " + name);
	Logger::LogInfo("[SceneManager] Currently Active Scene: " + m_ActiveScene->GetName());
}

void SceneManager::LoadScene(const std::string& sceneName, bool reloadScene)
{
	// Make sure scene exists
	assert(m_Scenes.find(sceneName) != m_Scenes.end());

	// Set active
	m_ActiveScene = m_Scenes[sceneName];
	UI->ChangeScene(sceneName);
	SOUNDMANAGER->ChangeScene();

	// Reload if necessary
	if (reloadScene) m_ActiveScene->Reload();

	Logger::LogInfo("[SceneManager] Switching Scene...");
	Logger::LogInfo("[SceneManager] Currently Active Scene: " + m_ActiveScene->GetName());
}
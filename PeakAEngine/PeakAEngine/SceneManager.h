#pragma once
#include <functional>

#include "Singleton.h"

#define SCENEMANAGER SceneManager::GetInstance()

class Scene;
class GameObject;

class SceneManager final : public Singleton<SceneManager>
{
public:
	~SceneManager() override = default;

	SceneManager(const SceneManager& other) = delete;
	SceneManager(SceneManager&& other) noexcept = delete;
	SceneManager& operator=(const SceneManager& other) = delete;
	SceneManager& operator=(SceneManager&& other) noexcept = delete;

	void RegisterScene(const std::string& name, const std::function<void(Scene*)>& instructions);
	void LoadScene(const std::string& sceneName);

	void DrawImGui() const;
	void Update() const;
	void FixedUpdate() const;
	void Render() const;
	void RenderGizmos() const;
	void ChangeSceneGraph();

private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;

	std::map<std::string, std::function<void(Scene*)>> m_SceneInstructions;
	std::shared_ptr<Scene> m_ActiveScene{};

	bool m_NewSceneShouldLoad{ false };
	std::string m_WantedSceneName{};
};


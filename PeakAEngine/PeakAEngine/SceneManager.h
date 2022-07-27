#pragma once
#include <functional>

#include "Manager.h"

class Scene;
class GameObject;

class SceneManager final : public Manager
{
public:
	SceneManager() = default;
	~SceneManager() override;

	SceneManager(const SceneManager& other) = delete;
	SceneManager(SceneManager&& other) noexcept = delete;
	SceneManager& operator=(const SceneManager& other) = delete;
	SceneManager& operator=(SceneManager&& other) noexcept = delete;

	void AddScene(const std::string& name, Scene* scene);
	void LoadScene(const std::string& sceneName);

	void DrawImGui() const;
	void Update() const;
	void FixedUpdate() const;
	void Render() const;
	void RenderGizmos() const;
	void ChangeSceneGraph();

	Scene* GetActiveScene() const { return m_ActiveScene; }
private:
	std::map<std::string, Scene*> m_Scenes{};
	Scene* m_ActiveScene{};
};


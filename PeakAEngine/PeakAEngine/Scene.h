#pragma once

#include "GameObject.h"
class PhysicsHandler;

struct SceneSettings 
{
	bool enableGUI = false;
};

class Scene
{
public:
	Scene();
	virtual ~Scene();

	const std::string& GetName() const;
	void SetName(const std::string& name);

	GameObject* AddChild(const std::string& name);
	std::vector<GameObject*> GetObjects() const;

	PhysicsHandler* GetPhysicsHandler() const { return m_pPhysicsHandler.get(); }

	virtual void Initialize() {}
	virtual void Reload() {}

	void RootInitialize();
	void DrawImGui();
	void Update() const;
	void FixedUpdate() const;
	void Render() const;
	void RenderGizmos() const;
	void ChangeSceneGraph();

	void OnHover(const glm::vec2& mousePos);
	void OnClick();

	template<typename T>
	inline T* FindObjectOfType() const
	{
		for (auto& obj : m_Objects)
		{
			T* objOfType = obj->GetComponent<T>();
			if (objOfType)
				return objOfType;
		}
		return nullptr;
	}
	template<typename T>
	inline std::vector<T*> FindObjectsOfType() const
	{
		std::vector<T*> objects;

		for (auto obj : m_Objects)
		{
			T* objOfType = obj->GetComponent<T>();
			if (objOfType)
				objects.push_back(objOfType);
		}
		return objects;
	}

	SceneSettings& GetSettings() { return m_Settings; }
private: 
	SceneSettings m_Settings{};

	std::string m_Name;

	std::unique_ptr<PhysicsHandler> m_pPhysicsHandler{};

	std::vector<std::shared_ptr<GameObject>> m_Objects{};
	std::vector<std::shared_ptr<GameObject>> m_ObjectsToAdd{};

	static unsigned int m_IdCounter;
};


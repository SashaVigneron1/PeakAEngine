#pragma once

class PhysicsHandler;
class GameObject;

class Scene final
{
public:
	~Scene();

	const std::string& GetName() const;

	GameObject* CreateChildObject(const std::string& name);
	std::vector<GameObject*> GetObjects() const;

	PhysicsHandler* GetPhysicsHandler() const { return m_pPhysicsHandler.get(); }

private:
	friend class SceneManager;
	explicit Scene(const std::string& name);

	void Initialize() const;
	void DrawImGui();
	void Update() const;
	void FixedUpdate() const;
	void Render() const;
	void RenderGizmos() const;
	void ChangeSceneGraph();

	void DisplaySceneGraph();
	void DisplayObjectInSceneGraph(GameObject* pObject);

	GameObject* m_pSelectedObjectInHierarchy{};

	std::string m_Name;

	std::unique_ptr<PhysicsHandler> m_pPhysicsHandler{};

	std::vector<std::shared_ptr<GameObject>> m_Objects{};
	std::vector<std::shared_ptr<GameObject>> m_ObjectsToAdd{};

	static unsigned int m_IdCounter;
};


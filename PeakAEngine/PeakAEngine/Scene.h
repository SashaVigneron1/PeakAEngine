#pragma once

class PhysicsHandler;
class GameObject;

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
	
	void RootInitialize();
	void DrawImGui();
	void Update() const;
	void FixedUpdate() const;
	void Render() const;
	void RenderGizmos() const;
	void ChangeSceneGraph();

private: 
	std::string m_Name;

	std::unique_ptr<PhysicsHandler> m_pPhysicsHandler{};

	std::vector<std::shared_ptr<GameObject>> m_Objects{};
	std::vector<std::shared_ptr<GameObject>> m_ObjectsToAdd{};

	static unsigned int m_IdCounter;
};


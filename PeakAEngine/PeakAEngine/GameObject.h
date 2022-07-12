#pragma once

class BoxCollider;
class Scene;
class Component;
class Transform;

class GameObject final
{
public:
	// Name
	const std::string& GetName() const;
	void SetName(const std::string& name);

	// Tag
	const std::string& GetTag() const;
	void SetTag(const std::string& tag, bool changeChildren = false);

	// Components
	template<typename componentType, typename... argTypes>
	componentType* CreateComponent(argTypes&&... args);

	template<typename typeToFind>
	typeToFind* GetComponent() const;

	template<typename typeToFind>
	std::vector<typeToFind*> GetComponents() const;

	Transform* GetTransform() const;

	// Children - Parent
	GameObject* CreateChildObject(const std::string& name);
	std::vector<GameObject*> GetChildren() const;
	GameObject* GetParent() const;

	Scene* GetScene() const { return m_Scene; }

	void SetEnabled(bool enabled);
	bool IsEnabled() const;

	// Destruction
	void Destroy();
	bool IsMarkedForDestroy() const;

private:
	friend class Scene;
	friend class BoxCollider;
	GameObject(const std::string& name, GameObject* parent, Scene* scene);

	void Initialize() const;
	void Update() const;
	void FixedUpdate() const;
	void DrawImGui() const;
	void DrawProperties() const;
	void Render() const;
	void RenderGizmos() const;

	void OnTriggerEnter(BoxCollider* other) const;
	void OnTriggerExit(BoxCollider* other) const;
	void OnCollisionEnter(BoxCollider* other) const;
	void OnCollisionExit(BoxCollider* other) const;

	void OnEnable() const;
	void OnDisable() const;
	void OnDestroy() const;

	void ChangeSceneGraph();

	std::string m_Name;
	std::string m_Tag{ "Default" };

	//Transform* m_pTransform;
	std::vector<std::shared_ptr<Component>> m_Components;
	std::vector<std::shared_ptr<Component>> m_ComponentsToAdd;
	Transform* m_pTransform;

	std::vector<std::shared_ptr<GameObject>> m_Children;
	std::vector<std::shared_ptr<GameObject>> m_ChildrenToAdd;
	GameObject* m_pParentGameObject = nullptr;

	Scene* m_Scene;

	bool m_IsMarkedForDestroy = false;

	bool m_IsEnabled{ true };
	bool m_ShouldBeEnabled{ true };


	void SetBoxCollider(BoxCollider* pCollider) { m_BoxCollider = pCollider; }

	bool IsHovering(const glm::vec2& mousePos) const;
	bool IsHovered() const { return m_CursorIsHoveringThis; }
	bool SetHovering(bool value) { m_CursorIsHoveringThis = value; }

	void OnBeginHover();
	void OnEndHover();
	void OnClick();

	bool m_CursorIsHoveringThis = false;

	BoxCollider* m_BoxCollider = nullptr;
};

template<typename componentType, typename... argTypes>
componentType* GameObject::CreateComponent(argTypes&&... args)
{
	// Can't create more than 1 transform
	/*if (typeid(componentType) == typeid(Transform) && GetComponent<Transform>() != nullptr)
		return nullptr;*/

	// Create component and add it
	auto component = std::shared_ptr<componentType>(new componentType(args...));
	component->SetGameObject(this);
	const auto pComponent = component.get();

	m_ComponentsToAdd.push_back(component);

	return pComponent;
}

template<typename typeToFind>
typeToFind* GameObject::GetComponent() const
{
	auto it = std::find_if(
		m_Components.begin(),
		m_Components.end(),
		[](const std::shared_ptr<Component>& component)
		{
			return typeid(typeToFind) == typeid(*component);
		});

	if (it == m_Components.end())
		return nullptr;

	return dynamic_cast<typeToFind*>((*it).get());
}

template<typename typeToFind>
std::vector<typeToFind*> GameObject::GetComponents() const
{
	std::vector<typeToFind*> returnVector{};

	for (const auto& component : m_Components)
	{
		if (typeid(typeToFind) == typeid(*component))
			returnVector.push_back(dynamic_cast<typeToFind*>(component.get()));
	}

	return returnVector;
}


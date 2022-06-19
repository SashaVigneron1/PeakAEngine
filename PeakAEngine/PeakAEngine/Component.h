#pragma once

class BoxCollider;
class GameObject;

class Component
{
public:
	Component() = default;
	virtual ~Component() = default;
	Component(const Component& other) = delete;
	Component(Component&& other) noexcept = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) noexcept = delete;

	virtual void Initialize() {}
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void DrawImGui() {}
	virtual void Render() const {}
	virtual void RenderGizmos() const {}

	virtual void OnTriggerEnter(BoxCollider*) {}
	virtual void OnTriggerExit(BoxCollider*) {}
	virtual void OnCollisionEnter(BoxCollider*) {}
	virtual void OnCollisionExit(BoxCollider*) {}

	virtual void OnEnable() {}
	virtual void OnDisable() {}
	virtual void OnDestroy() {}

	void SetGameObject(GameObject* pGameObject);
	GameObject* GetGameObject() const { return m_pGameObject; }

	virtual void Destroy() { m_IsMarkedForDestroy = true;  }
	bool IsMarkedForDestroy() const { return m_IsMarkedForDestroy; }

	bool IsEnabled() const { return m_IsEnabled; }
	void SetEnabled(bool enabled) { m_IsEnabled = enabled; }

protected:
	GameObject* m_pGameObject = nullptr;
	
	bool m_IsMarkedForDestroy = false;
	bool m_IsEnabled = false;
};


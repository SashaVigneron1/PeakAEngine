#include "PeakAEnginePCH.h"
#include "GameObject.h"

#include "Component.h"
#include "Transform.h"
#include "BoxCollider.h"

GameObject::GameObject(const std::string& name, GameObject* parent, Scene* scene)
	: m_Name{ name }
	, m_pTransform{ CreateComponent<Transform>() }
	, m_pParentGameObject{ parent }
	, m_Scene{ scene }
{
	if (m_pParentGameObject != nullptr)
		m_Tag = m_pParentGameObject->GetTag();
}

void GameObject::Initialize() const
{
	// Update components
	for (const auto& pComponent : m_Components)
	{
		if (pComponent->IsEnabled())
			pComponent->Initialize();
	}

	// Update children
	for (const auto& pChild : m_Children)
	{
		if (pChild->IsEnabled())
			pChild->Initialize();
	}
}

void GameObject::Update() const
{
	// Update components
	for (const auto& pComponent : m_Components)
	{
		if (pComponent->IsEnabled())
			pComponent->Update();
	}

	// Update children
	for (const auto& pChild : m_Children)
	{
		if (pChild->IsEnabled())
			pChild->Update();
	}
}

void GameObject::FixedUpdate() const
{
	// Update Components
	for (const auto& pComponent : m_Components)
	{
		if (pComponent->IsEnabled())
			pComponent->FixedUpdate();
	}

	// Update children
	for (const auto& pChild : m_Children)
	{
		if (pChild->IsEnabled())
			pChild->FixedUpdate();
	}
}

void GameObject::DrawImGui() const
{
	// Update components
	for (const auto& pComponent : m_Components)
	{
		if (pComponent->IsEnabled())
			pComponent->DrawImGui();
	}

	// Update children
	for (const auto& pChild : m_Children)
	{
		if (pChild->IsEnabled())
			pChild->DrawImGui();
	}
}



void GameObject::Render() const
{
	// Render Components
	for (const auto& pComponent : m_Components)
	{
		if (pComponent->IsEnabled())
			pComponent->Render();
	}

	// Render children
	for (const auto& pChild : m_Children)
	{
		if (pChild->IsEnabled())
			pChild->Render();
	}
}

void GameObject::RenderGizmos() const
{
	// Render Components
	for (const auto& pComponent : m_Components)
	{
		if (pComponent->IsEnabled())
			pComponent->RenderGizmos();
	}

	// Render children
	for (const auto& pChild : m_Children)
	{
		if (pChild->IsEnabled())
			pChild->RenderGizmos();
	}
}


void GameObject::OnTriggerEnter(BoxCollider* other) const
{
	for (const auto& pComponent : m_Components)
	{
		if (pComponent->IsEnabled() && m_IsEnabled)
			pComponent->OnTriggerEnter(other);
	}
}

void GameObject::OnTriggerExit(BoxCollider* other) const
{
	for (const auto& pComponent : m_Components)
	{
		if (pComponent->IsEnabled() && m_IsEnabled)
			pComponent->OnTriggerExit(other);
	}
}

void GameObject::OnCollisionEnter(BoxCollider* other) const
{
	for (const auto& pComponent : m_Components)
	{
		if (pComponent->IsEnabled() && m_IsEnabled)
			pComponent->OnCollisionEnter(other);
	}
}

void GameObject::OnCollisionExit(BoxCollider* other) const
{
	for (const auto& pComponent : m_Components)
	{
		if (pComponent->IsEnabled() && m_IsEnabled)
			pComponent->OnCollisionExit(other);
	}
}

void GameObject::OnEnable() const
{
	for (const auto& pComponent : m_Components)
	{
		if (pComponent->IsEnabled())
			pComponent->OnEnable();
	}

	for (const auto& pChild : m_Children)
	{
		if (pChild->IsEnabled())
			pChild->OnEnable();
	}
}

void GameObject::OnDisable() const
{
	for (const auto& pComponent : m_Components)
	{
		if (pComponent->IsEnabled())
			pComponent->OnDisable();
	}

	for (const auto& pChild : m_Children)
	{
		if (pChild->IsEnabled())
			pChild->OnDisable();
	}
}

void GameObject::OnDestroy() const
{
	for (const auto& pChild : m_Children)
	{
		pChild->OnDestroy();
	}

	for (const auto& pComponent : m_Components)
	{
		pComponent->OnDestroy();
	}
}


bool GameObject::IsHovering(const glm::vec2& mousePos) const
{
	if (!m_BoxCollider)
		return false;

	return m_BoxCollider->IsMouseOverlapping(mousePos, true);
}

void GameObject::OnBeginHover()
{
	for (const auto& pComponent : m_Components)
	{
		if (pComponent->IsEnabled())
			pComponent->OnBeginHover();
	}

	for (const auto& pChild : m_Children)
	{
		if (pChild->IsEnabled())
			pChild->OnBeginHover();
	}

	m_CursorIsHoveringThis = true;
}

void GameObject::OnEndHover()
{
	for (const auto& pComponent : m_Components)
	{
		if (pComponent->IsEnabled())
			pComponent->OnEndHover();
	}

	for (const auto& pChild : m_Children)
	{
		if (pChild->IsEnabled())
			pChild->OnEndHover();
	}

	m_CursorIsHoveringThis = false;
}

void GameObject::OnClick()
{
	for (const auto& pComponent : m_Components)
	{
		if (pComponent->IsEnabled())
			pComponent->OnClick();
	}

	for (const auto& pChild : m_Children)
	{
		if (pChild->IsEnabled())
			pChild->OnClick();
	}
}


void GameObject::ChangeSceneGraph()
{
	// Enable Disable
	if (m_ShouldBeEnabled && !m_IsEnabled)
		OnEnable();

	if (!m_ShouldBeEnabled && m_IsEnabled)
		OnDisable();

	m_IsEnabled = m_ShouldBeEnabled;

	// Add Children
	for (const auto& pChild : m_ChildrenToAdd)
		m_Children.push_back(pChild);

	for (const auto& pChild : m_ChildrenToAdd)
		pChild->Initialize();

	m_ChildrenToAdd.clear();

	// Add Components
	for (const auto& pComponent : m_ComponentsToAdd)
		m_Components.push_back(pComponent);

	for (const auto& pComponent : m_ComponentsToAdd)
		pComponent->Initialize();

	m_ComponentsToAdd.clear();

	// Destroy marked objects
	for (const auto& child : m_Children)
	{
		if (child->IsMarkedForDestroy())
			child->OnDestroy();
	}

	const auto pos = std::remove_if(m_Children.begin(), m_Children.end(),
		[](const auto& o) { return o->IsMarkedForDestroy(); });

	m_Children.erase(pos, m_Children.end());

	// Destroy marked components
	for (const auto& comp : m_Components)
	{
		if (comp->IsMarkedForDestroy())
			comp->OnDestroy();
	}

	const auto pos2 = std::remove_if(m_Components.begin(), m_Components.end(),
		[](const auto& c) { return c->IsMarkedForDestroy(); });

	m_Components.erase(pos2, m_Components.end());

	// Call on remaining objects
	for (auto& object : m_Children)
	{
		object->ChangeSceneGraph();
	}

	// Call on remaining components
	for (auto& component : m_Components)
	{
		component;
		//component->ChangeSceneGraph();
	}
}

const std::string& GameObject::GetName() const
{
	return m_Name;
}

void GameObject::SetName(const std::string& name)
{
	m_Name = name;
}

const std::string& GameObject::GetTag() const
{
	return m_Tag;
}

void GameObject::SetTag(const std::string& tag, bool changeChildren)
{
	m_Tag = tag;

	// change children?
	if (changeChildren)
	{
		for (const auto& pChild : m_Children)
		{
			pChild->SetTag(tag, true);
		}
	}
}

Transform* GameObject::GetTransform() const
{
	return m_pTransform;
}

GameObject* GameObject::CreateChildObject(const std::string& name)
{
	const auto child = std::shared_ptr<GameObject>(new GameObject(name, this, m_Scene)); // Can't use make_shared because of private constructor
	const auto pChild = child.get();

	m_ChildrenToAdd.push_back(child);

	return pChild;
}

std::vector<GameObject*> GameObject::GetChildren() const
{
	std::vector<GameObject*> vecRaw;

	vecRaw.reserve(m_Children.size());
	std::transform(m_Children.cbegin(), m_Children.cend(), std::back_inserter(vecRaw),
		[](auto& ptr) { return ptr.get(); });

	return vecRaw;
}

GameObject* GameObject::GetParent() const
{
	return m_pParentGameObject;
}

void GameObject::SetEnabled(bool enabled)
{
	m_ShouldBeEnabled = enabled;
}

bool GameObject::IsEnabled() const
{
	return m_IsEnabled;
}

void GameObject::Destroy()
{
	m_IsMarkedForDestroy = true;
}

bool GameObject::IsMarkedForDestroy() const
{
	return m_IsMarkedForDestroy;
}
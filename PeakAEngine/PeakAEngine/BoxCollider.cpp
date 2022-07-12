#include "PeakAEnginePCH.h"
#include "BoxCollider.h"

#include "GameObject.h"
#include "RigidBody.h"
#include "Transform.h"

#include "RenderManager.h"

#include "SpriteRenderer.h"

#pragma warning(push, 0)
#include <b2_fixture.h>
#pragma warning(pop)

BoxCollider::BoxCollider(const glm::vec2& size, const glm::vec2& offset, float angle, bool isTrigger)
	: m_Size(size)
	, m_Offset(offset)
	, m_Rotation(angle)
	, m_IsTrigger{ isTrigger }
	, m_ShouldCalculateSize{ false }
{}

BoxCollider::BoxCollider(const glm::vec2& offset, float angle, bool isTrigger)
	: m_Size(1,1)
	, m_Offset(offset)
	, m_Rotation(angle)
	, m_IsTrigger{ isTrigger }
	, m_ShouldCalculateSize{ true }
{
	
}

void BoxCollider::Initialize()
{
	if (m_ShouldCalculateSize)
	{
		SpriteRenderer* spriteRenderer = GetGameObject()->GetComponent<SpriteRenderer>();
		if (spriteRenderer)
		{
			m_Size = glm::vec2{ spriteRenderer->GetSpriteDimensions().x / spriteRenderer->GetPixelsPerUnit(),
			spriteRenderer->GetSpriteDimensions().y / spriteRenderer->GetPixelsPerUnit() };
		}
		else
		{
			Logger::LogError("[BoxCollider] No Sprite Renderer Was Found. Using A Default Size Of {1,1}");
		}
	}

	AttachToRigidbody(GetGameObject());
}

void BoxCollider::Update()
{
	if (m_RigidbodyChanged)
	{
		if (m_pRigidbody != nullptr)
		{
			m_pRigidbody->RemoveBoxCollider(this);
			m_pRigidbody = nullptr;
		}

		AttachToRigidbody(GetGameObject());
		m_RigidbodyChanged = false;
	}
}


void BoxCollider::OnEnable()
{
	if (m_pRigidbody != nullptr)
		m_pRigidbody->AddBoxCollider(this);
}

void BoxCollider::OnDisable()
{
	if (m_pRigidbody != nullptr)
		m_pRigidbody->RemoveBoxCollider(this);
}

void BoxCollider::OnDestroy()
{
	if (m_pRigidbody != nullptr)
		m_pRigidbody->RemoveBoxCollider(this);
}

const glm::vec2& BoxCollider::GetSize() const
{
	return m_Size;
}

void BoxCollider::SetSize(const glm::vec2& size)
{
	m_Size = size;
	RecalculateShape();
}

const glm::vec2& BoxCollider::GetOffset() const
{
	return m_Offset;
}

void BoxCollider::SetOffset(const glm::vec2& offset)
{
	m_Offset = offset;
	RecalculateShape();
}

float BoxCollider::GetRotation() const
{
	return m_Rotation;
}

void BoxCollider::SetRotation(float angle)
{
	m_Rotation = angle;
	RecalculateShape();
}

bool BoxCollider::IsTrigger() const
{
	return m_IsTrigger;
}

void BoxCollider::SetTrigger(bool isTrigger)
{
	m_RunTimeFixture->SetSensor(isTrigger);
	m_IsTrigger = isTrigger;
}

void BoxCollider::RigidBodyChanged()
{
	m_RigidbodyChanged = true;
	m_pRigidbody = nullptr;
	m_RunTimeFixture = nullptr;
}

void BoxCollider::RecalculateShape()
{
	if (IsEnabled() && m_pRigidbody != nullptr)
	{
		m_pRigidbody->RemoveBoxCollider(this);
		m_pRigidbody->AddBoxCollider(this);
	}
}

void BoxCollider::NotifyGameObjectOnTriggerEnter(BoxCollider* other) const
{
	GetGameObject()->OnTriggerEnter(other);
}

void BoxCollider::NotifyGameObjectOnTriggerExit(BoxCollider* other) const
{
	GetGameObject()->OnTriggerExit(other);
}

void BoxCollider::NotifyGameObjectOnCollisionEnter(BoxCollider* other) const
{
	GetGameObject()->OnCollisionEnter(other);
}

void BoxCollider::NotifyGameObjectOnCollisionExit(BoxCollider* other) const
{
	GetGameObject()->OnCollisionExit(other);
}

void BoxCollider::AttachToRigidbody(const GameObject* gameObject)
{
	const auto rb = gameObject->GetComponent<RigidBody>();

	if (rb != nullptr)
	{
		rb->AddBoxCollider(this);
		m_pRigidbody = rb;
	}
	else
	{
		const auto parent = gameObject->GetParent();
		if (parent != nullptr)
		{
			AttachToRigidbody(parent);
		}
		else
		{
			Logger::LogError("[BoxCollider] Could not find RigidBodyComponent to attach to.");
		}
	}
}


void BoxCollider::RenderGizmos() const
{
	if (!m_DrawDebugRect)
		return;

	glm::vec2 pos{ m_pGameObject->GetTransform()->GetWorldPosition().x + m_Offset.x, m_pGameObject->GetTransform()->GetWorldPosition().y + m_Offset.y };
	glm::vec2 size{ m_pGameObject->GetTransform()->GetWorldScale().x * m_Size.x, m_pGameObject->GetTransform()->GetWorldScale().y * m_Size.y};

	pos.x -= size.x / 2;
	pos.y -= size.y / 2;

	//ToDo: Rotation

	RENDERER.RenderDebugRect({ pos.x, pos.y, size.x, size.y }, true, m_DebugColor);
}

//void BoxCollider::DrawProperties()
//{
//	ImGuiHelper::Component("Box Collider Component", this, &m_ShouldBeEnabled, [&]()
//		{
//			bool isTrigger = IsTrigger();
//			ImGuiHelper::ItemLabel("Is Trigger", ImGuiHelper::ItemLabelAlignment::Left);
//			if (ImGui::Checkbox("##IsTrigger", &isTrigger))
//				SetTrigger(isTrigger);
//
//			glm::vec2 size = GetSize();
//			ImGuiHelper::ItemLabel("Size", ImGuiHelper::ItemLabelAlignment::Left);
//			if (ImGui::DragFloat2("##Size", &size.x, 0.1f))
//				SetSize(size);
//
//			glm::vec2 offset = GetOffset();
//			ImGuiHelper::ItemLabel("Offset", ImGuiHelper::ItemLabelAlignment::Left);
//			if (ImGui::DragFloat2("##Offset", &offset.x, 0.1f))
//				SetOffset(offset);
//
//			float rotation = GetRotation();
//			ImGuiHelper::ItemLabel("Rotation", ImGuiHelper::ItemLabelAlignment::Left);
//			if (ImGui::DragFloat("##Rotation", &rotation))
//				SetRotation(rotation);
//		});
//}


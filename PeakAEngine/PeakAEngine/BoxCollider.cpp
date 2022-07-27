#include "PeakAEnginePCH.h"
#include "BoxCollider.h"

#include "GameObject.h"
#include "RigidBody.h"
#include "Transform.h"

#include "Managers.h"

#include "CameraComponent.h"

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
			m_SpriteRenderer = spriteRenderer;
		}
		else
		{
			Logger::LogError("[BoxCollider] No Sprite Renderer Was Found. Using A Default Size Of {1,1}");
		}
	}

	GetGameObject()->SetBoxCollider(this);
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

bool BoxCollider::IsMouseOverlapping(const glm::vec2& pos, bool convertToScreenSpace)
{
	// Put Mouse Relative To Center Of Screen
	auto position = pos;
	position -= RENDERER->GetWindowSize() / 2.f;

	// Calculate ScreenPos
	glm::vec2 thisPos{ m_pGameObject->GetTransform()->GetWorldPosition().x + m_Offset.x
		, m_pGameObject->GetTransform()->GetWorldPosition().y + m_Offset.y };
	glm::vec2 size{ m_pGameObject->GetTransform()->GetWorldScale().x * m_Size.x, 
		m_pGameObject->GetTransform()->GetWorldScale().y * m_Size.y };

	// Take Camera Pos Into Account
	thisPos -= RENDERER->GetCamera()->GetGameObject()->GetTransform()->GetWorldPosition();

	// Create Vertices
	float vertexLeft{ -size.x/2 };
	float vertexBottom{ -size.y/2 };
	float vertexRight{ size.x/2 };
	float vertexTop{ size.y/2 };

	// Apply Rotation
	constexpr float inverse180{ 1.f / 180.f * float(M_PI) };
	float rotation = m_pGameObject->GetTransform()->GetWorldRotation();

	float cosAngle = cos(rotation * inverse180);
	float sinAngle = sin(rotation * inverse180);

	glm::vec2 vertices[4]{};
	vertices[0] = { vertexLeft * cosAngle - vertexBottom * sinAngle, vertexBottom * cosAngle + vertexLeft * sinAngle };
	vertices[1] = { vertexLeft * cosAngle - vertexTop * sinAngle, vertexTop * cosAngle + vertexLeft * sinAngle };
	vertices[2] = { vertexRight * cosAngle - vertexTop * sinAngle, vertexTop * cosAngle + vertexRight * sinAngle };
	vertices[3] = { vertexRight * cosAngle - vertexBottom * sinAngle, vertexBottom * cosAngle + vertexRight * sinAngle };

	// Apply Transformation
	vertices[0] += thisPos;
	vertices[1] += thisPos;
	vertices[2] += thisPos;
	vertices[3] += thisPos;

	// Apply Screen Space
	if (convertToScreenSpace)
	{
		vertices[0] *= RENDERER->GetPixelsPerUnit();
		vertices[1] *= RENDERER->GetPixelsPerUnit();
		vertices[2] *= RENDERER->GetPixelsPerUnit();
		vertices[3] *= RENDERER->GetPixelsPerUnit();
	}

	// Check If Overlapping
	float minX{FLT_MAX};
	float minY{FLT_MAX};
	float maxX{FLT_MIN};
	float maxY{FLT_MIN};

	for (auto vPos : vertices)
		(vPos.x < minX) ? minX = vPos.x : minX = minX;
	for (auto vPos : vertices)
		(vPos.y < minY) ? minY = vPos.y : minY = minY;
	for (auto vPos : vertices)
		(vPos.x > maxX) ? maxX = vPos.x : maxX = maxX;
	for (auto vPos : vertices)
		(vPos.y > maxY) ? maxY = vPos.y : maxY = maxY;

	return (
		position.x > minX
		&& position.x < maxX
		&& position.y > minY
		&& position.y < maxY
		);

	//Todoo: Fix: If the collider is rotated; The corners of the rotated rectangle also count
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

	RENDERER->RenderDebugRect({ pos.x, pos.y, size.x, size.y }, true, m_DebugColor, m_pGameObject->GetTransform()->GetWorldRotation());
}



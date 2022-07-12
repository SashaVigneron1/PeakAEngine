#include "PeakAEnginePCH.h"
#include "RigidBody.h"

#pragma warning(push, 0)
#include <b2_body.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#pragma warning(pop)

#include "imgui.h"

#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"
#include "PhysicsHandler.h"
#include "BoxCollider.h"
//#include "Mage/ImGui/ImGuiHelper.h"

RigidBody::RigidBody(BodyType type, bool fixedRotation, float gravityScale)
	: m_InitialType{ type }
	, m_InitialFixedRotation{ fixedRotation }
	, m_InitialGravityScale{ gravityScale }
	, m_PhysicsMaterial{ }
{}

RigidBody::RigidBody(BodyType type, const PhysicsMaterial& material, bool fixedRotation, float gravityScale)
	: m_InitialType{ type }
	, m_InitialFixedRotation{ fixedRotation }
	, m_InitialGravityScale{ gravityScale }
	, m_PhysicsMaterial{ material }
{
}

void RigidBody::Initialize()
{
	GetGameObject()->GetScene()->GetPhysicsHandler()->AddRigidBody(this, static_cast<int>(m_InitialType), m_InitialFixedRotation, m_InitialGravityScale);
	TransformChanged();
	NotifyBoxCollidersOfChange(GetGameObject());
}

void RigidBody::OnDestroy()
{
	GetGameObject()->GetScene()->GetPhysicsHandler()->RemoveRigidBody(this);
	NotifyBoxCollidersOfChange(GetGameObject());
}

void RigidBody::NotifyBoxCollidersOfChange(const GameObject* gameObject) const
{
	for (const auto& col : gameObject->GetComponents<BoxCollider>())
	{
		col->RigidBodyChanged();
	}

	for (const auto& child : gameObject->GetChildren())
	{
		if (child->GetComponent<RigidBody>() != nullptr)
			NotifyBoxCollidersOfChange(child);
	}
}

void RigidBody::AddBoxCollider(BoxCollider* boxCollider) const
{
	const auto objectScale = boxCollider->GetGameObject()->GetTransform()->GetWorldScale();
	const auto objectOffset = boxCollider->GetGameObject()->GetTransform()->GetWorldPosition() - GetGameObject()->GetTransform()->GetWorldPosition();
	const auto objectRotationOffset = boxCollider->GetGameObject()->GetTransform()->GetWorldRotation() - GetGameObject()->GetTransform()->GetWorldRotation();

	b2PolygonShape boxShape;
	boxShape.SetAsBox(
		boxCollider->GetSize().x / 2.f * objectScale.x, boxCollider->GetSize().y / 2.f * objectScale.y,
		{ objectOffset.x + boxCollider->GetOffset().x * objectScale.x, objectOffset.y + boxCollider->GetOffset().y * objectScale.y },
		boxCollider->GetRotation() + objectRotationOffset);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.isSensor = boxCollider->IsTrigger();
	fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(boxCollider);

	fixtureDef.density = m_PhysicsMaterial.density;
	fixtureDef.friction = m_PhysicsMaterial.friction;
	fixtureDef.restitution = m_PhysicsMaterial.restitution;
	fixtureDef.restitutionThreshold = m_PhysicsMaterial.restitutionThreshold;

	const auto fixture = m_RunTimeBody->CreateFixture(&fixtureDef);

	boxCollider->SetRunTimeFixture(fixture);
}

void RigidBody::RemoveBoxCollider(BoxCollider* boxCollider) const
{
	m_RunTimeBody->DestroyFixture(boxCollider->GetRunTimeFixture());
	boxCollider->SetRunTimeFixture(nullptr);
}

void RigidBody::TransformChanged() const
{
	const auto transform = GetGameObject()->GetTransform();
	m_RunTimeBody->SetTransform(
		b2Vec2(transform->GetWorldPosition().x, transform->GetWorldPosition().y),
		glm::radians(transform->GetWorldRotation())
	);
	m_RunTimeBody->SetAwake(true);
}

void RigidBody::UpdateTransform() const
{
	GetGameObject()->GetTransform()->SetWorldPositionWithoutUpdatingRigidBody({ m_RunTimeBody->GetPosition().x, m_RunTimeBody->GetPosition().y });
	GetGameObject()->GetTransform()->SetWorldRotationWithoutUpdatingRigidBody(glm::degrees(m_RunTimeBody->GetAngle()));
}

RigidBody::BodyType RigidBody::GetType() const
{
	return static_cast<BodyType>(m_RunTimeBody->GetType());
}

void RigidBody::SetType(BodyType type) const
{
	m_RunTimeBody->SetType(static_cast<b2BodyType>(type));
	m_RunTimeBody->SetAwake(true);
}

bool RigidBody::GetFixedRotation() const
{
	return m_RunTimeBody->IsFixedRotation();
}

void RigidBody::SetFixedRotation(bool fixedRotation) const
{
	m_RunTimeBody->SetFixedRotation(fixedRotation);
	m_RunTimeBody->SetAwake(true);
}

float RigidBody::GetGravityScale() const
{
	return m_RunTimeBody->GetGravityScale();
}

void RigidBody::SetGravityScale(float gravityScale) const
{
	m_RunTimeBody->SetGravityScale(gravityScale);
	m_RunTimeBody->SetAwake(true);
}

void RigidBody::SetVelocity(const glm::vec2& velocity) const
{
	m_RunTimeBody->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

glm::vec2 RigidBody::GetVelocity() const
{
	return { m_RunTimeBody->GetLinearVelocity().x, m_RunTimeBody->GetLinearVelocity().y };
}

void RigidBody::ApplyForce(const glm::vec2& force, bool wake) const
{
	m_RunTimeBody->ApplyForceToCenter(b2Vec2(force.x, force.y), wake);
}

void RigidBody::ApplyImpulse(const glm::vec2& impulse, bool wake) const
{
	m_RunTimeBody->ApplyLinearImpulseToCenter(b2Vec2(impulse.x, impulse.y), wake);
}

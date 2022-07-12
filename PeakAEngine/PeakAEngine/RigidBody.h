#pragma once
#include "Component.h"

class b2Body;

class RigidBody final : public Component
{
public:
	enum class BodyType
	{
		Static,
		Kinematic,
		Dynamic
	};
	struct PhysicsMaterial 
	{
		float density = 1.f;
		float friction = 0.5f;
		float restitution = 0.5f;
		float restitutionThreshold = 0.5f;
	};

	RigidBody(BodyType type, bool fixedRotation = false, float gravityScale = 1.0f);
	RigidBody(BodyType type, const PhysicsMaterial& material, bool fixedRotation = false, float gravityScale = 1.0f);
	virtual ~RigidBody() override = default;

	RigidBody(const RigidBody& other) = delete;
	RigidBody(RigidBody&& other) = delete;
	RigidBody& operator=(const RigidBody& other) = delete;
	RigidBody& operator=(RigidBody&& other) = delete;

	void Initialize() override;
	void OnDestroy() override;
	void RenderGizmos() const override {}

	BodyType GetType() const;
	void SetType(BodyType type) const;

	bool GetFixedRotation() const;
	void SetFixedRotation(bool fixedRotation) const;

	float GetGravityScale() const;
	void SetGravityScale(float gravityScale) const;

	glm::vec2 GetVelocity() const;
	void SetVelocity(const glm::vec2& velocity) const;

	void ApplyForce(const glm::vec2& force, bool wake = true) const;
	void ApplyImpulse(const glm::vec2& impulse, bool wake = true) const;

private:
	friend class PhysicsHandler;
	friend class BoxCollider;
	friend class Transform;

	void TransformChanged() const;
	void UpdateTransform() const;

	void SetRunTimeBody(b2Body* body) { m_RunTimeBody = body; }
	b2Body* GetRunTimeBody() const { return m_RunTimeBody; }

	void AddBoxCollider(BoxCollider* boxCollider) const;
	void RemoveBoxCollider(BoxCollider* boxCollider) const;

	void NotifyBoxCollidersOfChange(const GameObject* gameObject) const;

	BodyType m_InitialType;
	bool m_InitialFixedRotation;
	float m_InitialGravityScale;

	b2Body* m_RunTimeBody = nullptr;

	PhysicsMaterial m_PhysicsMaterial;
};


#pragma once
#include "Component.h"
class RigidBody;

class Transform final : public Component
{

public:
	//void DrawProperties() override;

	glm::mat3x3 GetWorldMatrix();

	// Position
	const glm::vec2& GetLocalPosition() const { return m_Position; }
	glm::vec2 GetWorldPosition();

	void SetLocalPosition(const glm::vec2& position);
	void SetWorldPosition(const glm::vec2& position);

	void Translate(const glm::vec2& translation);

	// Rotation
	float GetLocalRotation() const { return m_Rotation; }
	float GetWorldRotation();

	void SetLocalRotation(float rotation);
	void SetWorldRotation(float rotation);

	void Rotate(float rotation);

	// Scale
	const glm::vec2& GetLocalScale() const { return m_Position; }
	glm::vec2 GetWorldScale();

	void SetLocalScale(const glm::vec2& scale);
	void SetWorldScale(const glm::vec2& scale);

	void Scale(const glm::vec2& factor);

	// Transform can't be destroyed
	void Destroy() override {}

private:
	friend class RigidBody;

	void TransformChanged(bool updateRigidBody);
	void SetWorldPositionWithoutUpdatingRigidBody(const glm::vec2& position);
	void SetWorldRotationWithoutUpdatingRigidBody(float rotation);

	glm::vec2 m_Position{ 0.f, 0.f };
	float m_Rotation{ 0.f };
	glm::vec2 m_Scale{ 1.f, 1.f };

	glm::mat3x3 m_WorldMatrix;
	bool m_WorldMatrixDirty{ true };

};


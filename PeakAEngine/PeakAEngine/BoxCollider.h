#pragma once
#include "Component.h"

class b2Fixture;
class SpriteRenderer;

class BoxCollider final : public Component
{

public:
	BoxCollider(const glm::vec2& size, const glm::vec2& offset, float angle, bool isTrigger = false);
	BoxCollider(const glm::vec2& offset, float angle, bool isTrigger = false);

	void Initialize() override;
	void OnEnable() override;
	void OnDisable() override;
	void OnDestroy() override;
	void Update() override;
	void RenderGizmos() const override;

	const glm::vec2& GetSize() const;
	void SetSize(const glm::vec2& size);

	const glm::vec2& GetOffset() const;
	void SetOffset(const glm::vec2& offset);

	float GetRotation() const;
	void SetRotation(float angle);

	bool IsTrigger() const;
	void SetTrigger(bool isTrigger);

	void EnableDebugDrawing(bool value) { m_DrawDebugRect = value; }
	void SetDebugColor(const SDL_Color& color) { m_DebugColor = color; }

	bool IsOverlapping(const glm::vec2& pos, bool convertToScreenSpace = false);
private:
	friend class PhysicsHandler;
	friend class RigidBody;
	friend class Transform;

	b2Fixture* GetRunTimeFixture() const { return m_RunTimeFixture; }
	void SetRunTimeFixture(b2Fixture* fixture) { m_RunTimeFixture = fixture; }

	void RigidBodyChanged();

	void RecalculateShape();

	void NotifyGameObjectOnTriggerEnter(BoxCollider* other) const;
	void NotifyGameObjectOnTriggerExit(BoxCollider* other) const;
	void NotifyGameObjectOnCollisionEnter(BoxCollider* other) const;
	void NotifyGameObjectOnCollisionExit(BoxCollider* other) const;

	void AttachToRigidbody(const GameObject* gameObject);

	// Collider shape
	glm::vec2 m_Size = { 1.f, 1.f };
	glm::vec2 m_Offset = { 0.f, 0.f };
	float m_Rotation = 0.f;

	bool m_IsTrigger = false;

	RigidBody* m_pRigidbody = nullptr;
	bool m_RigidbodyChanged = false;

	// storage for runtime
	b2Fixture* m_RunTimeFixture = nullptr;

	bool m_DrawDebugRect{ false };
	SDL_Color m_DebugColor{ 255,0,0,100 };


	// SpriteRenderer Dependencies
	SpriteRenderer* m_SpriteRenderer{ nullptr };
	bool m_ShouldCalculateSize{ false };

};


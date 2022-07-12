#include "pch.h"
#include "TestComponent.h"

#include "PeakAEngine/InputManager.h"

#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Transform.h"

#include "imgui.h"

#include "PeakAEngine/RigidBody.h"
#include "PeakAEngine/RenderManager.h"

TestComponent::TestComponent() 
	: Component()
{

}

void TestComponent::Update()
{
	if (INPUTMANAGER.IsDown('d'))
	{
		m_pGameObject->GetTransform()->Translate({ 100 * Time::DeltaTime(),0 });

		//m_pGameObject->GetComponent<RigidBody>()->ApplyImpulse({ 100,0 }, true);

		m_IsMoving = true;
	}
	else {
		m_IsMoving = false;
	}
}

void TestComponent::DrawImGui()
{
	ImGui::Checkbox("Moving to the right", &m_IsMoving);
}

void TestComponent::RenderGizmos() const
{
	/*SDL_Color color{ 0,0,255,255 };
	glm::vec2 pos{ m_pGameObject->GetTransform()->GetWorldPosition().x, m_pGameObject->GetTransform()->GetWorldPosition().y };
	RENDERER.RenderDebugRect({ pos.x, pos.y,100,100 }, true, color);*/
}

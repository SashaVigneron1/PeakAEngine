#include "pch.h"
#include "TestComponent.h"

#include "PeakAEngine/InputManager.h"

#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Transform.h"

#include "imgui.h"

//ToDoo: Remove Header Dependency-ish (boxcollider & rendermanager)
#include "PeakAEngine/RigidBody.h"
#include "PeakAEngine/RenderManager.h"
#include "PeakAEngine/BoxCollider.h"	

TestComponent::TestComponent() 
	: Component()
{

}

void TestComponent::Update()
{
	/*if (INPUTMANAGER.GetMouseButton(MouseButton::LMB))
	{
		Logger::LogInfo("LMB Was Holded");
	}*/
	/*if (INPUTMANAGER.GetMouseButtonPressed(MouseButton::LMB))
	{
		Logger::LogInfo("LMB Was Clicked");
	}*/
	/*if (INPUTMANAGER.GetMouseButtonUp(MouseButton::LMB))
	{
		Logger::LogInfo("LMB Was Released");
	}*/

	if (INPUTMANAGER.IsDown('d'))
	{
		m_pGameObject->GetTransform()->Translate({ 10 * Time::DeltaTime(),0 });

		//m_pGameObject->GetComponent<RigidBody>()->ApplyImpulse({ 100,0 }, true);

		m_IsMoving = true;
	}
	if (INPUTMANAGER.IsDown('q'))
	{
		m_pGameObject->GetTransform()->Translate({ -10 * Time::DeltaTime(),0 });

		//m_pGameObject->GetComponent<RigidBody>()->ApplyImpulse({ 100,0 }, true);

		m_IsMoving = true;
	}
	if (INPUTMANAGER.IsDown('z'))
	{
		m_pGameObject->GetTransform()->Translate({ 0,10 * Time::DeltaTime() });

		//m_pGameObject->GetComponent<RigidBody>()->ApplyImpulse({ 100,0 }, true);

		m_IsMoving = true;
	}
	if (INPUTMANAGER.IsDown('s'))
	{
		m_pGameObject->GetTransform()->Translate({ 0,-10 * Time::DeltaTime() });

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


void TestComponent::OnBeginHover()
{
	Logger::LogInfo("Begin Hover");
	SDL_Color color{ 0, 0, 255, 100 };
	GetGameObject()->GetComponent<BoxCollider>()->SetDebugColor(color);
}

void TestComponent::OnEndHover()
{
	Logger::LogInfo("End Hover");
	SDL_Color color{ 255, 0, 0, 100 };
	GetGameObject()->GetComponent<BoxCollider>()->SetDebugColor(color);
}

void TestComponent::OnClick()
{
	Logger::LogInfo("Click");
	SDL_Color color{ 0, 255, 0, 100 };
	GetGameObject()->GetComponent<BoxCollider>()->SetDebugColor(color);
}

TestCommand::TestCommand(TestComponent* pTestComponent)
	: Command{}
	, m_pTestComponent{ pTestComponent }
{
}

void TestCommand::Execute()
{
	Logger::LogInfo("This is a test");
}

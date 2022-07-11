#include "pch.h"
#include "TestComponent.h"

#include "PeakAEngine/InputManager.h"

#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Transform.h"

#include "imgui.h"

TestComponent::TestComponent() 
	: Component()
{

}

void TestComponent::Update()
{
	if (INPUTMANAGER.IsDown('d'))
	{
		m_pGameObject->GetTransform()->Translate({ 100 * Time::DeltaTime(),0});
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

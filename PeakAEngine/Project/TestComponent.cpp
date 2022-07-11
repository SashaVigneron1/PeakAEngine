#include "pch.h"
#include "TestComponent.h"

#include "PeakAEngine/InputManager.h"

#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Transform.h"

TestComponent::TestComponent() 
	: Component()
{

}

void TestComponent::Update()
{
	if (INPUTMANAGER.IsDown('d'))
	{
		m_pGameObject->GetTransform()->Translate({ 100 * Time::DeltaTime(),0});
	}
}

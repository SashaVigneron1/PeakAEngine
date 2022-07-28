#include "pch.h"
#include "TestComponent.h"

#include "PeakAEngine/Managers.h"
#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Transform.h"

#include "TestPlayerState.h"

TestComponent::TestComponent(TestPlayerState* playerState)
	: Component()
	, m_State{ playerState }
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

	if (INPUTMANAGER->IsDown('d'))
	{
		m_pGameObject->GetTransform()->Translate({ 10 * Time::DeltaTime(),0 });

		//m_pGameObject->GetComponent<RigidBody>()->ApplyImpulse({ 100,0 }, true);

		m_IsMoving = true;
	}
	else if (INPUTMANAGER->IsDown('q'))
	{
		m_pGameObject->GetTransform()->Translate({ -10 * Time::DeltaTime(),0 });

		//m_pGameObject->GetComponent<RigidBody>()->ApplyImpulse({ 100,0 }, true);

		m_IsMoving = true;
	}
	else if (INPUTMANAGER->IsDown('z'))
	{
		m_pGameObject->GetTransform()->Translate({ 0,10 * Time::DeltaTime() });

		//m_pGameObject->GetComponent<RigidBody>()->ApplyImpulse({ 100,0 }, true);

		m_IsMoving = true;
	}
	else if (INPUTMANAGER->IsDown('s'))
	{
		m_pGameObject->GetTransform()->Translate({ 0,-10 * Time::DeltaTime() });

		//m_pGameObject->GetComponent<RigidBody>()->ApplyImpulse({ 100,0 }, true);

		m_IsMoving = true;
	}
	else {
		m_IsMoving = false;
	}



	//if (m_IsMoving)
	//{
	//	//Send Message To Server
	//	NETWORKMANAGER->SendGameMessage(GameNetworkMessage(
	//		GameMessageType::ObjectUpdated, "testObject",
	//		m_State->SerializeObjectStateData()
	//	));
	//}
}
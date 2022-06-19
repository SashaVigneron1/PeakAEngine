#include "PeakAEnginePCH.h"
#include "Component.h"

void Component::SetGameObject(GameObject* pGameObject)
{
	if (m_pGameObject == nullptr)
		m_pGameObject = pGameObject;
}

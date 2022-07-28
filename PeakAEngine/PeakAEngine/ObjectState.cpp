#include "PeakAEnginePCH.h"
#include "ObjectState.h"

#include "GameObject.h"
#include "Transform.h"

ObjectState::ObjectState(const std::string& displayName, const std::string& id)
	: m_DisplayName{ displayName }
	, m_PeerId{ id }
	, m_Position{ }
    , m_pGameObject{ nullptr }
{
}

void ObjectState::DeserializeObjectStateData(const std::vector<uint8_t>& data)
{
    ObjectStateData rcvdPlayerStateData = ObjectStateData();
    CopyMemory(&rcvdPlayerStateData, data.data(), sizeof(ObjectStateData));

    if (rcvdPlayerStateData.newPos != m_Position)
    {
        auto transform = m_pGameObject->GetTransform();

        glm::vec2 diffVector{ rcvdPlayerStateData.newPos - m_Position };

        transform->Translate(diffVector);
        m_Position = transform->GetWorldPosition();
    }
}

std::vector<uint8_t> ObjectState::SerializeObjectStateData()
{
    std::vector<uint8_t> data(sizeof(ObjectStateData));
    if (!m_pGameObject)
        return data;

    ObjectStateData objectStateData = { m_pGameObject->GetTransform()->GetWorldPosition() };

    CopyMemory(data.data(), &objectStateData, sizeof(ObjectStateData));

    return data;
}

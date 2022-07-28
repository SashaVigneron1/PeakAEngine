#include "pch.h"
#include "TestPlayerState.h"

#include "PeakAEngine/Managers.h"

#include "PeakAEngine/Scene.h"
#include "PeakAEngine/GameObject.h"
#include "PeakAEngine/Transform.h"

#include "PeakAEngine/SpriteRenderer.h"
#include "PeakAEngine/BoxCollider.h"
#include "PeakAEngine/RigidBody.h"
#include "TestComponent.h"

TestPlayerState::TestPlayerState(bool hasInput)
    : ObjectState(PLAYFABMANAGER->GetEntityKey().Id, "testObject")
{
    auto scene = SCENEMANAGER->GetActiveScene();
    auto go = scene->AddChild("testObject");
    SpriteRenderer* spriteRenderer = go->CreateComponent<SpriteRenderer>();
    spriteRenderer->AddSprite("Walking", std::make_shared<Sprite>("Character/PeterPepper_Walking.png",
        std::vector<SpriteRow>{
        SpriteRow{ Direction::FacingCamera, 0 },
            SpriteRow{ Direction::FacingLeft, 1 },
            SpriteRow{ Direction::FacingRight, 1, true },
            SpriteRow{ Direction::FacingAwayFromCamera, 2 },
    },
        3, 1 / 6.f, glm::vec2{ 1,1 }, 0));
    spriteRenderer->SetActiveSprite("Walking");
    spriteRenderer->SetEnabled(true);
    spriteRenderer->SetPixelsPerUnit(16);

    if (hasInput)
    {
        go->CreateComponent<RigidBody>(RigidBody::BodyType::Dynamic, RigidBody::PhysicsMaterial{ 1.f,0.f,0.f,1.f }, true, 10.f);
        auto collider = go->CreateComponent<BoxCollider>(glm::vec2{ 0,0 }, 0.f, false);
        collider->SetEnabled(true);
        collider->SetDebugColor({ 0,0,255,100 });
        collider->EnableDebugDrawing(true);

        auto test = go->CreateComponent<TestComponent>(this);
        test->SetEnabled(true);
    }

    go->GetTransform()->SetWorldPosition({ 0,0 });
    go->GetTransform()->SetWorldScale({ 1, 1 });
    go->GetTransform()->Rotate(45.f);

    m_pGameObject = go;
    m_pGameObject->SetObjectState(this);

    m_OldPos = { 0,0 };
}

TestPlayerState::~TestPlayerState()
{
    m_pGameObject->Destroy();
}

void TestPlayerState::DeserializeObjectStateData(const std::vector<uint8_t>& data)
{
    TestPlayerStateData rcvdPlayerStateData = TestPlayerStateData();
    CopyMemory(&rcvdPlayerStateData, data.data(), sizeof(TestPlayerStateData));

    if (rcvdPlayerStateData.newPos != m_OldPos)
    {
        auto transform = m_pGameObject->GetTransform();

        glm::vec2 diffVector{ rcvdPlayerStateData.newPos - m_OldPos };

        transform->Translate(diffVector);
        m_OldPos = transform->GetWorldPosition();
    }
}

std::vector<uint8_t> TestPlayerState::SerializeObjectStateData()
{
    TestPlayerStateData playerStateData = { m_pGameObject->GetTransform()->GetWorldPosition() };

    std::vector<uint8_t> data(sizeof(TestPlayerStateData));
    CopyMemory(data.data(), &playerStateData, sizeof(TestPlayerStateData));

    return data;
}

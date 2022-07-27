#include "PeakAEnginePCH.h"
#include "PlayerState.h"

#include "Managers.h"
#include "Scene.h"

#include "GameObject.h"
#include "Transform.h"

#include "SpriteRenderer.h"
#include "BoxCollider.h"
#include "RigidBody.h"
#include "TestComponent.h"

PlayerState::PlayerState(const char* displayName, bool controlInput)
    : m_DisplayName{displayName}
{
    //ToDoo: Move this to game project?
    // Instantiate Player Object
    auto scene = SCENEMANAGER->GetActiveScene();
    auto go = scene->AddChild(displayName);
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

    go->CreateComponent<RigidBody>(RigidBody::BodyType::Dynamic, RigidBody::PhysicsMaterial{ 1.f,0.f,0.f,1.f }, true, 10.f);
    auto collider = go->CreateComponent<BoxCollider>(glm::vec2{ 0,0 }, 0.f, false);
    collider->SetEnabled(true);
    collider->SetDebugColor({ 0,0,255,100 });
    collider->EnableDebugDrawing(true);

    if (controlInput)
    {
        auto test = go->CreateComponent<TestComponent>();
        test->SetEnabled(true);
        test->SetPlayerState(this);
    }

    go->GetTransform()->SetWorldPosition({ 0,0 });
    go->GetTransform()->SetWorldScale({ 1, 1 });
    go->GetTransform()->Rotate(45.f);
    
    m_pGameObject = go;

    m_OldPos = { 0,0 };
}

PlayerState::~PlayerState()
{
    m_pGameObject->Destroy();
}

void PlayerState::DeserializePlayerStateData(const std::vector<uint8_t>& data)
{
    PlayerStateData rcvdPlayerStateData = PlayerStateData();
    CopyMemory(&rcvdPlayerStateData, data.data(), sizeof(PlayerStateData));

    if (rcvdPlayerStateData.newPos != m_OldPos)
    {
        auto go = GetGameObject();
        auto transform = go->GetTransform();

        glm::vec2 diffVector{ rcvdPlayerStateData.newPos - m_OldPos };

        transform->Translate(diffVector);
        m_OldPos = transform->GetWorldPosition();
    }
}

std::vector<uint8_t> PlayerState::SerializePlayerStateData()
{
    PlayerStateData playerStateData = { GetGameObject()->GetTransform()->GetWorldPosition() };

    std::vector<uint8_t> data(sizeof(PlayerStateData));
    CopyMemory(data.data(), &playerStateData, sizeof(PlayerStateData));

    return data;
}
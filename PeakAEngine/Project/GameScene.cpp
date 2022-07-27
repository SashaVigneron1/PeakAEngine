#include "pch.h"
#include "GameScene.h"

//ToDoo: fix linker error
#include "PeakAEngine/GameObject.h"

#include "PeakAEngine/InputManager.h"
#include "PeakAEngine/ResourceManager.h"
#include "PeakAEngine/TestComponent.h"
#include "PeakAEngine/RenderComponent.h"
#include "PeakAEngine/RigidBody.h"
#include "PeakAEngine/BoxCollider.h"

#include "PeakAEngine/Transform.h"
#include "PeakAEngine/CameraComponent.h"
#include <PeakAEngine/SpriteRenderer.h>

#include "PeakAEngine/UIManager.h"
#include "PeakAEngine/UI_Button.h"
#include "PeakAEngine/UI_Text.h"
#include "PeakAEngine/UI_InputField.h"

#include "PeakAEngine/SceneManager.h"
#include "PeakAEngine/PlayfabManager.h"
#include "PeakAEngine/NetworkManager.h"



GameScene::GameScene()
	: Scene{}
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize()
{



	// GROUND OBJECT
	auto go = AddChild("GroundObj");
	auto spriteRenderer = go->CreateComponent<SpriteRenderer>();
	spriteRenderer->AddSprite("Walking", new  Sprite("Character/PeterPepper_Idle.png",
		{
				SpriteRow{Direction::FacingCamera, 0},
				SpriteRow{Direction::FacingLeft, 1},
				SpriteRow{Direction::FacingRight, 1, true},
				SpriteRow{Direction::FacingAwayFromCamera, 2},
		},
		3, 1, { 1,1 }, 0));
	spriteRenderer->SetActiveSprite("Walking");
	spriteRenderer->SetEnabled(true);
	spriteRenderer->SetPixelsPerUnit(16);

	auto test = go->CreateComponent<TestComponent>();
	test->SetEnabled(false);

	go->GetTransform()->SetWorldPosition({ 0,-1 });
	go->GetTransform()->SetWorldScale({ 30, 1 });

	go->CreateComponent<RigidBody>(RigidBody::BodyType::Static, RigidBody::PhysicsMaterial{ 1.f,0.f,0.f,1.f });
	auto collider = go->CreateComponent<BoxCollider>(glm::vec2{ 0,0 }, 0.f, false);
	collider->SetEnabled(true);
	collider->SetDebugColor({ 0,255,0,100 });
	collider->EnableDebugDrawing(true);




}

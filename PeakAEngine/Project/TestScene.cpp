#include "pch.h"
#include "TestScene.h"

#include "PeakAEngine/GameObject.h"

#include "PeakAEngine/ResourceManager.h"
#include "TestComponent.h"
#include "PeakAEngine/RenderComponent.h"
#include "PeakAEngine/RigidBody.h"
#include "PeakAEngine/BoxCollider.h"

#include "PeakAEngine/Transform.h"
#include "PeakAEngine/CameraComponent.h"
#include <PeakAEngine/SpriteRenderer.h>

TestScene::TestScene()
	: Scene{ }
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
	// SETTINGS
	GetSettings().enableGUI = true;



	// PLAYER OBJ
	auto go = AddChild("PlayerObj");
	SpriteRenderer* spriteRenderer = go->CreateComponent<SpriteRenderer>();
	spriteRenderer->AddSprite("Walking", new  Sprite("Character/PeterPepper_Walking.png",
		{
				SpriteRow{Direction::FacingCamera, 0},
				SpriteRow{Direction::FacingLeft, 1},
				SpriteRow{Direction::FacingRight, 1, true},
				SpriteRow{Direction::FacingAwayFromCamera, 2},
		},
		3, 1 / 6.0f, { 1,1 }, 0));
	spriteRenderer->SetActiveSprite("Walking");
	spriteRenderer->SetEnabled(true);
	spriteRenderer->SetPixelsPerUnit(16);

	go->CreateComponent<RigidBody>(RigidBody::BodyType::Dynamic, true, 10.f);
	auto collider = go->CreateComponent<BoxCollider>(glm::vec2{0,0}, 0.f, false);
	collider->SetEnabled(true);
	collider->SetDebugColor({ 0,0,255,100 });
	collider->EnableDebugDrawing(true);

	auto test = go->CreateComponent<TestComponent>();
	test->SetEnabled(true);

	go->GetTransform()->SetWorldPosition({ 0,0 });
	go->GetTransform()->SetWorldScale({ 1, 1 });

	// CAMERA
	auto cameraObj = AddChild("Camera");
	cameraObj->CreateComponent<CameraComponent>();
	cameraObj->GetTransform()->Scale({1, 1});


	// GROUND OBJECT
	go = AddChild("GroundObj");
	spriteRenderer = go->CreateComponent<SpriteRenderer>();
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

	test = go->CreateComponent<TestComponent>();
	test->SetEnabled(false);

	go->GetTransform()->SetWorldPosition({ 0,-1 });
	go->GetTransform()->SetWorldScale({ 30, 1 });

	go->CreateComponent<RigidBody>(RigidBody::BodyType::Static);
	collider = go->CreateComponent<BoxCollider>(glm::vec2{0,0}, 0.f, false);
	collider->SetEnabled(true);
	collider->SetDebugColor({ 0,255,0,100 });
	collider->EnableDebugDrawing(true);
}

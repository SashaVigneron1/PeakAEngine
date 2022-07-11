#include "pch.h"
#include "TestScene.h"

#include "PeakAEngine/GameObject.h"

#include "PeakAEngine/ResourceManager.h"
#include "TestComponent.h"
#include "PeakAEngine/RenderComponent.h"

#include "PeakAEngine/Transform.h"
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
	GetSettings().enableGUI = true;

	//auto go = AddChild("TestObject");
	///*auto comp =	go->CreateComponent<TestComponent>();
	//comp->SetEnabled(true);*/

	//auto renderer = go->CreateComponent<RenderComponent>();
	//renderer->SetTexture(RESOURCEMANAGER.LoadTexture("Character/PeterPepper_Walking.png"));
	//
	//renderer->SetRenderLayer(0);

	//go->SetEnabled(true);
	//renderer->SetEnabled(true);
	//renderer->SetPivot({ 0.5f,0.5f });
	//renderer->SetSourceRect({ 0 ,0, 16, 16 });


	//go->GetTransform()->SetWorldPosition({1280/2,720/2});
	//go->GetTransform()->SetWorldScale({ 5,5 });

	auto go = AddChild("SpriteTestObject");
	SpriteRenderer* spriteRenderer = go->CreateComponent<SpriteRenderer>();
	spriteRenderer->AddSprite("Walking", new  Sprite("Character/PeterPepper_Walking.png",
		{
				SpriteRow{Direction::FacingCamera, 0},
				SpriteRow{Direction::FacingLeft, 1},
				SpriteRow{Direction::FacingRight, 1, true},
				SpriteRow{Direction::FacingAwayFromCamera, 2},
		},
		3, 1 / 6.0f, {1,1}, 3));
	spriteRenderer->SetActiveSprite("Walking");
	spriteRenderer->SetEnabled(true);

	auto test = go->CreateComponent<TestComponent>();
	test->SetEnabled(true);

	go->GetTransform()->SetWorldPosition({1280/2,720/2});
	go->GetTransform()->SetWorldScale({ 10, 10 });



}

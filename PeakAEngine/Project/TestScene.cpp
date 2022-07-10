#include "pch.h"
#include "TestScene.h"

#include "PeakAEngine/GameObject.h"

#include "TestComponent.h"

TestScene::TestScene()
	: Scene{ }
{
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
	Logger::LogInfo("I am the testscene!");

	auto go = AddChild("TestObject");
	auto comp =	go->CreateComponent<TestComponent>();
	comp->SetEnabled(true);

}

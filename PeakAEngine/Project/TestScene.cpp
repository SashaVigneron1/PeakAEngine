#include "pch.h"
#include "TestScene.h"

#include "PeakAEngine/GameObject.h"

#include "PeakAEngine/InputManager.h"
#include "PeakAEngine/ResourceManager.h"
#include "TestComponent.h"
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
#include "PeakAEngine/ServiceLocator.h"

#include "PeakAEngine/NetworkManager.h"

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

	// SOUND TEST
	SERVICELOCATOR.RegisterSoundSystem(new Logged_SoundSystem());
	int id = SERVICELOCATOR.GetSoundSystem()->AddClip("Resources/Sounds/BackgroundMusic.wav", -1);
	SERVICELOCATOR.GetSoundSystem()->Play(id);

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

	go->CreateComponent<RigidBody>(RigidBody::BodyType::Dynamic, RigidBody::PhysicsMaterial{ 1.f,0.f,0.f,1.f }, true, 10.f);
	auto collider = go->CreateComponent<BoxCollider>(glm::vec2{ 0,0 }, 0.f, false);
	collider->SetEnabled(true);
	collider->SetDebugColor({ 0,0,255,100 });
	collider->EnableDebugDrawing(true);

	auto test = go->CreateComponent<TestComponent>();
	test->SetEnabled(true);

	go->GetTransform()->SetWorldPosition({ 0,0 });
	go->GetTransform()->SetWorldScale({ 1, 1 });
	go->GetTransform()->Rotate(45.f);


	/*auto command = new TestCommand(test);
	command->SetButtonAction(ButtonActionType::IsDown);
	INPUTMANAGER.AddCommand('d', command);*/

	// CAMERA
	auto cameraObj = go->CreateChildObject("Camera");
	cameraObj->CreateComponent<CameraComponent>();
	cameraObj->GetTransform()->Scale({ 1, 1 });


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

	go->CreateComponent<RigidBody>(RigidBody::BodyType::Static, RigidBody::PhysicsMaterial{ 1.f,0.f,0.f,1.f });
	collider = go->CreateComponent<BoxCollider>(glm::vec2{ 0,0 }, 0.f, false);
	collider->SetEnabled(true);
	collider->SetDebugColor({ 0,255,0,100 });
	collider->EnableDebugDrawing(true);


	//UI.AddImage("Character/PeterPepper_Idle.png", { 10,10 }, { 100,100 }, { 0.f,0.f }, AnchorPosition::LeftBottom);
	/*UI.AddImage("Character/PeterPepper_Idle.png", { 10,10 }, { 100,100 }, { 1,0 }, AnchorPosition::RightBottom);
	UI.AddImage("Character/PeterPepper_Idle.png", { 10,10 }, { 100,100 }, { 0,1 }, AnchorPosition::LeftTop);
	UI.AddImage("Character/PeterPepper_Idle.png", { 10,10 }, { 100,100 }, { 1,1 }, AnchorPosition::RightTop);

	int button = UI.AddButton(new UI_Button("Character/PeterPepper_Idle.png", "Character/PeterPepper_Walking.png", "Character/PeterPepper_Death.png"
		, { 100,100 }, { 200,100 }, { 0.5f, 0.5f }, AnchorPosition::MiddleCenter));
	auto buttonElement = UI.GetUIElement(button);
	auto buttonB = static_cast<UI_Button*>(buttonElement);
	buttonB->SetFunctionToExecute([=]{
		Logger::LogInfo("This button was pressed!");
		});
	buttonB->AddText("Click Me", "UI/Cyber11.ttf", 0, TextAlignment::Center, 50);
	buttonB->SetTextColor({ 255,0,0,255 });

	int textId = UI.AddText("This Is Text.", "UI/Cyber11.ttf", 0, TextAlignment::Center
		, { 0,0 }, { 300,100 }, { 0.f, 0.f }, AnchorPosition::LeftBottom);
	
	auto element = UI.GetUIElement(textId);
	auto text = static_cast<UI_Text*>(element);
	text->ChangeText("This Is Also \nText.");*/

	

	// NETWORKING
	//NETWORKMANAGER.Init("68BA8");

	////NETWORKMANAGER.RegisterUser("PeakAlive", "PeakAlive", "sasha.vigneron@outlook.com");
	//NETWORKMANAGER.LoginUser("PeakAlive", "PeakAlive");
	//NETWORKMANAGER.ForceUpdate();

	//// Load Data
	//NETWORKMANAGER.LoadUserData();
	//NETWORKMANAGER.ForceUpdate();

	//std::map<std::string, std::string> userData;
	//userData = NETWORKMANAGER.GetDataMap();
	//Logger::LogMap("User Data: ", userData);

	//// Save Data
	//std::map<std::string, std::string> userDataToSave;
	//userDataToSave["Test"] = "1000";
	//userDataToSave["Test2"] = "10000";
	//userDataToSave["Test3"] = "100";
	//NETWORKMANAGER.SaveUserData(userDataToSave);
	//NETWORKMANAGER.ForceUpdate();

	//// Load New Data
	//NETWORKMANAGER.LoadUserData();
	//NETWORKMANAGER.ForceUpdate();
	//userData = NETWORKMANAGER.GetDataMap();
	//Logger::LogMap("User Data: ", userData);

}

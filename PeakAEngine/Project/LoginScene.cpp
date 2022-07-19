#include "pch.h"
#include "LoginScene.h"

//ToDoo: fix linker error
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

#include "PeakAEngine/PlayfabManager.h"


LoginScene::LoginScene()
	: Scene{}
{
}

LoginScene::~LoginScene()
{
}

void LoginScene::Initialize()
{
	int nrElements = 5;
	float yOffsetPerElement{ 120.f };
	glm::vec2 size{ 300.f, 100.f };
	glm::vec2 pos{ -size.x/2, ((nrElements+1)*size.y)/2 };

	// USERNAME
	pos.y -= yOffsetPerElement;
	int usernameInputId = UI.AddInputField("LoginScene", "Username", "UI/Cyber11.ttf", 0, 0, TextAlignment::Center, 20, "UI/White.jpg",
		pos, size, { 0.f,0.f }, AnchorPosition::MiddleCenter
	);
	auto usernameInputElement = UI.GetUIElement(usernameInputId);
	auto usernameInputField = static_cast<UI_InputField*>(usernameInputElement);

	// EMAIL
	pos.y -= yOffsetPerElement;
	int emailInputId = UI.AddInputField("LoginScene", "Email", "UI/Cyber11.ttf", 0, 0, TextAlignment::Center, 20, "UI/White.jpg",
		pos, size, { 0.f,0.f }, AnchorPosition::MiddleCenter
	);
	auto emailInputElement = UI.GetUIElement(emailInputId);
	auto emailInputField = static_cast<UI_InputField*>(emailInputElement);

	// PASSWORD
	pos.y -= yOffsetPerElement;
	int passwordInputId = UI.AddInputField("LoginScene", "Password", "UI/Cyber11.ttf", 0, 0, TextAlignment::Center, 20, "UI/White.jpg",
		pos, size, { 0.f,0.f }, AnchorPosition::MiddleCenter
	);
	auto passwordInputElement = UI.GetUIElement(passwordInputId);
	auto passwordInputField = static_cast<UI_InputField*>(passwordInputElement);
	passwordInputField->SetHideState(true);

	
	// LOGIN
	pos.y -= yOffsetPerElement;
	int loginButtonId = UI.AddButton("LoginScene", new UI_Button{ "Character/PeterPepper_Idle.png", "Character/PeterPepper_Idle.png", "Character/PeterPepper_Idle.png",
		pos, size, { 0.f,0.f }, AnchorPosition::MiddleCenter });
	auto loginButtonElement = UI.GetUIElement(loginButtonId);
	auto loginButton = static_cast<UI_Button*>(loginButtonElement);
	loginButton->AddText("Login", "UI/Cyber11.ttf", 0, TextAlignment::Center, 50);

	loginButton->SetFunctionToExecute([=]
		{
			std::string username = usernameInputField->GetText();
			std::string password = passwordInputField->GetText();

			PLAYFABMANAGER.LoginUser(username, password);
		});

	// REGISTER
	pos.y -= yOffsetPerElement;
	int registerButtonId = UI.AddButton("LoginScene", new UI_Button{ "Character/PeterPepper_Idle.png", "Character/PeterPepper_Idle.png", "Character/PeterPepper_Idle.png",
		pos, size, { 0.f,0.f }, AnchorPosition::MiddleCenter });
	auto registerButtonElement = UI.GetUIElement(registerButtonId);
	auto registerButton = static_cast<UI_Button*>(registerButtonElement);
	registerButton->AddText("Register", "UI/Cyber11.ttf", 0, TextAlignment::Center, 50);

	registerButton->SetFunctionToExecute([=]
		{
			std::string username = usernameInputField->GetText();
			std::string password = passwordInputField->GetText();
			std::string email = emailInputField->GetText();

			PLAYFABMANAGER.RegisterUser(username, password, email);
		});

	
}

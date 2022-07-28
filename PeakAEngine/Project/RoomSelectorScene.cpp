#include "pch.h"
#include "RoomSelectorScene.h"

#include "PeakAEngine/Managers.h"

#include "PeakAEngine/SpriteRenderer.h"
#include "PeakAEngine/RenderComponent.h"
#include "PeakAEngine/RigidBody.h"
#include "PeakAEngine/BoxCollider.h"

#include "PeakAEngine/UI_Button.h"

#include "PeakAEngine/Transform.h"
#include "PeakAEngine/GameObject.h"
#include "ChatBoxComponent.h"

#include "PeakAEngine/GameStateManager.h"


#include "GameNetworkManager.h"

RoomSelectorScene::RoomSelectorScene()
{
}

RoomSelectorScene::~RoomSelectorScene()
{
}

void RoomSelectorScene::Initialize()
{
	//int nrElements = 5;
	//float yOffsetPerElement{ 120.f };
	glm::vec2 size{ 300.f, 100.f };
	//glm::vec2 pos{ -size.x / 2, ((nrElements + 1) * size.y) / 2 };

	// CREATE ROOM
	int createRoomButtonId = UI->AddButton("RoomSelectorScene", new UI_Button{ "UI/White.jpg", "UI/White.jpg", "UI/White.jpg",
		{-size.x/2, -size.y/2}, size, {0.f,0.f}, AnchorPosition::MiddleCenter });
	auto createRoomButtonElement = UI->GetUIElement(createRoomButtonId);
	auto createRoomButton = static_cast<UI_Button*>(createRoomButtonElement);
	createRoomButton->AddText("CreateRoom", "UI/Cyber11.ttf", 0, TextAlignment::Left, 10);
	createRoomButton->SetTextColor({ 0,0,0,255 });

	createRoomButton->SetFunctionToExecute([=]
		{
			GAMESTATE->CreateLocalObject();

			NETWORKMANAGER->CreateAndConnectToNetwork("1", [=](std::string desc) {

				Json::Value functionParams;
				functionParams["roomId"] = "1";
				functionParams["networkDescriptor"] = desc.c_str();

				PLAYFABMANAGER->ExecuteCloudScript("save_network_descriptor", functionParams,
					[](const PlayFab::ClientModels::ExecuteCloudScriptResult& /*result*/, void* /*customData*/) {
						Logger::LogSuccess("[CLOUDSCRIPT] Descriptor Saved in Room Id 1");
					},
					[](const PlayFabError& error, void* /*customData*/)
					{
						Logger::LogError("[CLOUDSCRIPT] Couldn't Save Descriptor: " + error.ErrorMessage);
					});
				});

			SCENEMANAGER->LoadScene("GameScene");

			GameNetworkManager::GetInstance().CreateObject("testObject", PLAYFABMANAGER->GetEntityKey().Id, ObjectType::TestObject);
		});

	// JOIN ROOM
	int joinRoomButtonId = UI->AddButton("RoomSelectorScene", new UI_Button{ "UI/White.jpg", "UI/White.jpg", "UI/White.jpg",
		{-size.x / 2, -size.y / 2 - size.y * 1.1f}, size, {0.f,0.f}, AnchorPosition::MiddleCenter });
	auto joinRoomButtonElement = UI->GetUIElement(joinRoomButtonId);
	auto joinRoomButton = static_cast<UI_Button*>(joinRoomButtonElement);
	joinRoomButton->AddText("JoinRoom", "UI/Cyber11.ttf", 0, TextAlignment::Left, 10);
	joinRoomButton->SetTextColor({ 0,0,0,255 });

	joinRoomButton->SetFunctionToExecute([=]
		{
			GAMESTATE->CreateLocalObject();

			std::string descriptor;

			// RECEIVE SERIALIZED DESCRIPTOR
			Json::Value functionParams;
			functionParams["roomId"] = "1";

			PLAYFABMANAGER->ExecuteCloudScript("get_network_descriptor", functionParams,
				[&](const PlayFab::ClientModels::ExecuteCloudScriptResult& result, void* /*customData*/)
				{
					descriptor = result.Logs.back().Message;

					Logger::LogSuccess("[CLOUDSCRIPT] Succesfully received descriptor from Room Id 1");
				},
				[](const PlayFabError& error, void* /*customData*/)
				{
					Logger::LogError("[CLOUDSCRIPT] Couldn't Receive Descriptor: " + error.ErrorMessage);
				});

			PLAYFABMANAGER->ForceUpdate();

			// Connect To Network
			NETWORKMANAGER->ConnectToNetwork("1", descriptor.c_str(), [] 
				{
					// Load Scene
					SCENEMANAGER->LoadScene("GameScene");


					NETWORKMANAGER->ToggleVoiceChat(true);

					GameNetworkManager::GetInstance().CreateObject("testObject", PLAYFABMANAGER->GetEntityKey().Id, ObjectType::TestObject);

				});
		});

	// CHAT TEST
	/*auto go = AddChild("ChatObj");
	auto chat = go->CreateComponent<ChatBoxComponent>();
	chat->SetEnabled(true);*/






	
}

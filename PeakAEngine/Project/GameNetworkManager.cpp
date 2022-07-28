#include "pch.h"
#include "GameNetworkManager.h"

#include "PeakAEngine/Managers.h"
#include "PeakAEngine/GameNetworkMessage.h"

#include "TestPlayerState.h"


void GameNetworkManager::RunEventQueue()
{
	const auto& queue = GAMESTATE->GetQueue();

	for (auto message : queue)
	{
		switch (message.message.MessageType())
		{
			case GameMessageType::ObjectCreated:
			{
				CreateObject(message.message.ObjectName(), message.sender, (ObjectType)message.message.UnsignedValue(), false);
				break;
			}
		}
	}

	GAMESTATE->ClearQueue();
}

void GameNetworkManager::CreateObject(const std::string& name, const std::string& peer, ObjectType type, bool hasInput)
{
	// CreateObject Logic: 
	// User: GameNetworkManager::CreateObject(name, peer, type)
	// GameNetworkManager -> GAMESTATE: CreateObject(objstate, objname, objId)
	// GAMESTATE -> SendGameMessage -> GAMESTATE: ObjectCreated
	// ^ Only Sends Message To Other Users

	std::shared_ptr<ObjectState> object = nullptr;

	switch (type)
	{
		case ObjectType::TestObject:
		{
			object = std::make_shared<TestPlayerState>(hasInput);
			break;
		}
		default:
		{
			Logger::LogError("[GameNetworkManager] CreateObject: Object type not found: " + std::to_string((int)type));
		}
	}

	// Send To GameState
	object->SetTypeId((int)type);
	GAMESTATE->CreateObject(object, int(type), peer, name);
}

#pragma once

#include "NetworkEnums.h"
#include "PeakAEngine/Singleton.h"


class GameNetworkManager : public Singleton<GameNetworkManager>
{
public:
	void RunEventQueue();

    void CreateObject(const std::string& name, const std::string& peer, ObjectType type, bool hasInput = true);
private:
};


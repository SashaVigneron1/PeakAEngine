#pragma once

#include "PeakAEngine/ObjectState.h"

class GameObject;

struct TestPlayerStateData 
{
	glm::vec2 newPos;
};

class TestPlayerState : public ObjectState
{
public:
	TestPlayerState(bool hasInput);
	virtual ~TestPlayerState();

	virtual void DeserializeObjectStateData(const std::vector<uint8_t>& data) override;
	virtual std::vector<uint8_t> SerializeObjectStateData() override;
private:
	glm::vec2 m_OldPos;
	GameObject* m_pGameObject;
};


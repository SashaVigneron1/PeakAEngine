#pragma once
#include "PeakAEngine/Component.h"

class TestPlayerState;

class TestComponent : public Component
{
public:
	TestComponent(TestPlayerState* playerState);

	virtual void Update() override;

private:
	bool m_IsMoving{ false };
	TestPlayerState* m_State{};
};


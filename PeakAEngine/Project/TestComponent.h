#pragma once
#include "PeakAEngine/Component.h"

class TestComponent : public Component
{
public: 
	TestComponent();

	virtual void Update() override;
	virtual void DrawImGui() override;

private: 
	bool m_IsMoving{ false };
};


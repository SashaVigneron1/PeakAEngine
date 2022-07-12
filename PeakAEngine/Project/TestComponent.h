#pragma once
#include "PeakAEngine/Component.h"

class TestComponent : public Component
{
public: 
	TestComponent();

	virtual void Update() override;
	virtual void DrawImGui() override;
	virtual void RenderGizmos() const override;

	virtual void OnBeginHover() override;
	virtual void OnEndHover() override;
	virtual void OnClick() override;

private: 
	bool m_IsMoving{ false };
};


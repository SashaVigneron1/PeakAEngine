#pragma once
#include "PeakAEngine/Component.h"

#include "PeakAEngine/Command.h"



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

class TestCommand : public Command
{
public:
	TestCommand(TestComponent* pTestComponent);
	virtual ~TestCommand() override = default;
	TestCommand(const TestCommand& other) = delete;
	TestCommand(TestCommand&& other) noexcept = delete;
	TestCommand& operator=(const TestCommand& other) = delete;
	TestCommand& operator=(TestCommand&& other) noexcept = delete;

	virtual void Execute() override;
private:
	TestComponent* m_pTestComponent;
};
#pragma once

//ToDoo: Remove this
//ToDoo: Find a way to include this in playerstate (dynamic playerstate)

#include "Component.h"
#include "Command.h"

class PlayerState;

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

	void SetPlayerState(PlayerState* state) { m_PlayerState = state; }

private:
	bool m_IsMoving{ false };
	PlayerState* m_PlayerState;
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
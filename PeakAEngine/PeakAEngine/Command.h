#pragma once

enum class ButtonActionType
{
	IsDown,
	IsPressed,
	IsReleased
};

class Command
{
public:
	Command() = default;
	virtual ~Command() = default;
	Command(const Command& other) = delete;
	Command(Command&& other) noexcept = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other) noexcept = delete;

	virtual void Execute() = 0;
	void SetControllerIndex(int value) { m_ControllerIndex = value; }
	int GetControllerIndex() const { return m_ControllerIndex; }

	void SetButtonAction(ButtonActionType type) { m_ButtonActionType = type; }
	ButtonActionType GetButtonAction() const { return m_ButtonActionType; }
protected:
	int m_ControllerIndex = 0;
	ButtonActionType m_ButtonActionType = ButtonActionType::IsPressed;
private:

};
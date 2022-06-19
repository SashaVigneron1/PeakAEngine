#pragma once
#include "Singleton.h"

#include <unordered_map>

#define INPUTMANAGER InputManager::GetInstance()

enum class ControllerButton
{
	ButtonA = 0x1000,
	ButtonB = 0x2000,
	ButtonX = 0x4000,
	ButtonY = 0x8000
};

class Command;

struct KeyInput
{
	KeyInput(bool isDown = false, bool isPressed = false, bool isReleased = false)
		: isDown{ isDown }
		, isPressed{ isPressed }
		, isReleased{ isReleased }
	{
	}
	bool isDown = false;
	bool isPressed = false;
	bool isReleased = false;
};
class InputManager final : public Singleton<InputManager>
{

	friend class Singleton<InputManager>;

public:
	InputManager();
	virtual ~InputManager() override;

	InputManager(const InputManager& other) = delete;
	InputManager(InputManager&& other) noexcept = delete;
	InputManager& operator=(const InputManager& other) = delete;
	InputManager& operator=(InputManager&& other) noexcept = delete;

	void AddCommand(ControllerButton button, Command* pCommand, int controllerIndex = 0);
	void AddCommand(char sdlKey, Command* pCommand);
	void RemoveCommand(Command* pCommand);

	void HandleInput();
	bool ProcessInput();
	bool IsDown(ControllerButton button, int controllerIndex = 0) const;
	bool IsDown(char sdlKey);
	bool IsPressed(ControllerButton button, int controllerIndex = 0) const;
	bool IsPressed(char sdlKey);
	bool IsUp(ControllerButton button, int controllerIndex = 0) const;
	bool IsUp(char sdlKey);
private:
	class InputManagerImpl;
	InputManagerImpl* m_pInputManager;

	std::unordered_map<ControllerButton, std::vector<Command*>> m_ControllerCommands;
	std::unordered_map<char, std::vector<Command*>> m_KeyCommands;
	std::unordered_map<char, KeyInput> m_Keys;
};


#pragma once
#include "Manager.h"

#include <unordered_map>
#include <SDL.h>

enum class ControllerButton
{
	ButtonA = 0x1000,
	ButtonB = 0x2000,
	ButtonX = 0x4000,
	ButtonY = 0x8000
};
enum class MouseButton
{
	LMB = 0,
	RMB = 1,
	MMB = 2,
	None = 3
};
struct MouseState
{
	bool isDown = false;
	bool isPressed = false;
	bool isReleased = false;
	MouseButton button = MouseButton::None;
	glm::vec2 position = {0,0};
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
class InputManager final : public Manager
{
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

	bool IsUpperCase();
	bool IsATSymbolDown();

	bool GetMouseButton(MouseButton index);
	bool GetMouseButtonPressed(MouseButton index);
	bool GetMouseButtonUp(MouseButton index);

	MouseState GetMouseState() const { return m_MouseState; }

	std::vector<char> GetKeysPressedThisFrame() const;
private:
	class InputManagerImpl;
	InputManagerImpl* m_pInputManager;

	std::unordered_map<ControllerButton, std::vector<Command*>> m_ControllerCommands;
	std::unordered_map<char, std::vector<Command*>> m_KeyCommands;
	std::unordered_map<char, KeyInput> m_Keys;

	std::list<SDL_KeyCode> m_KeysToIgnore;

	MouseState m_MouseState;
};


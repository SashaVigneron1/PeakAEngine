#include "PeakAEnginePCH.h"
#include "InputManager.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#include <SDL.h>

#include "RenderManager.h"
#include "GUIManager.h"

#include "Command.h"

#pragma comment(lib, "XInput.lib")



#pragma region Impl
class InputManager::InputManagerImpl
{
public:
	InputManagerImpl();
	~InputManagerImpl();

	InputManagerImpl(const InputManagerImpl& other) = delete;
	InputManagerImpl(InputManagerImpl&& other) noexcept = delete;
	InputManagerImpl& operator=(const InputManagerImpl& other) = delete;
	InputManagerImpl& operator=(InputManagerImpl&& other) noexcept = delete;


	void ProcessInput();
	bool IsPressed(ControllerButton button, int controllerIndex = 0) const;
	bool IsDown(ControllerButton button, int controllerIndex = 0) const;
	bool IsUp(ControllerButton button, int controllerIndex = 0) const;
private:
	int m_NrOfPlayers = 2;

	XINPUT_STATE* m_CurrentState;
	XINPUT_STATE* m_PreviousState;

	int* m_CurrButtonsPressed;
	int* m_CurrButtonsReleased;
};

bool InputManager::InputManagerImpl::IsDown(ControllerButton button, int controllerIndex) const
{
	return m_CurrentState[controllerIndex].Gamepad.wButtons & (int)button;
}

bool InputManager::InputManagerImpl::IsPressed(ControllerButton button, int controllerIndex) const
{
	return m_CurrButtonsPressed[controllerIndex] & (int)button;
}

bool InputManager::InputManagerImpl::IsUp(ControllerButton button, int controllerIndex) const
{
	return m_CurrButtonsReleased[controllerIndex] & (int)button;
}

InputManager::InputManagerImpl::InputManagerImpl()
	: m_CurrentState{ nullptr }
	, m_PreviousState{ nullptr }
	, m_NrOfPlayers{ 2 }
	, m_CurrButtonsPressed{ nullptr }
	, m_CurrButtonsReleased{ nullptr }
{
	m_CurrentState = new XINPUT_STATE[m_NrOfPlayers]{};
	m_PreviousState = new XINPUT_STATE[m_NrOfPlayers]{};
	m_CurrButtonsPressed = new int[m_NrOfPlayers] {};
	m_CurrButtonsReleased = new int[m_NrOfPlayers] {};
}

InputManager::InputManagerImpl::~InputManagerImpl()
{
	delete[] m_CurrentState;
	delete[] m_PreviousState;
	delete[] m_CurrButtonsPressed;
	delete[] m_CurrButtonsReleased;
}


void InputManager::InputManagerImpl::ProcessInput()
{
	for (int i = 0; i < m_NrOfPlayers; i++)
	{
		CopyMemory(&m_PreviousState[i], &m_CurrentState[i], sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState[i], sizeof(XINPUT_STATE));
		XInputGetState(i, &m_CurrentState[i]);

		auto buttonChanges = m_CurrentState[i].Gamepad.wButtons ^ m_PreviousState[i].Gamepad.wButtons;
		m_CurrButtonsPressed[i] = buttonChanges & m_CurrentState[i].Gamepad.wButtons;
		m_CurrButtonsReleased[i] = buttonChanges & (-m_CurrentState[i].Gamepad.wButtons);
	}
}

#pragma endregion

#pragma region InputManager
InputManager::InputManager()
	: m_pInputManager{ new InputManagerImpl{} }
{
}

InputManager::~InputManager()
{
	delete m_pInputManager;

	for (const auto& [button, commands] : m_ControllerCommands)
	{
		for (Command* pCommand : commands) delete pCommand;
	}
}

void InputManager::AddCommand(ControllerButton button, Command* pCommand, int controllerIndex)
{
	pCommand->SetControllerIndex(controllerIndex);
	m_ControllerCommands[button].push_back(pCommand);
}
void InputManager::AddCommand(char sdlKey, Command* pCommand)
{
	m_KeyCommands[sdlKey].push_back(pCommand);
}

void InputManager::RemoveCommand(Command* pCommand)
{

	if (m_ControllerCommands.size() > 0)
	{
		for (auto& [button, commands] : m_ControllerCommands)
		{
			for (int i{}; i < (int)commands.size(); ++i)
			{
				if (pCommand == commands[i])
				{
					delete pCommand;
					commands[i] = commands.back();
					commands.pop_back();
				}
			}
		}
	}

	if (m_KeyCommands.size() > 0)
	{
		for (auto& [button, commands] : m_KeyCommands)
		{
			for (int i{}; i < (int)commands.size(); ++i)
			{
				if (pCommand == commands[i])
				{
					delete pCommand;
					commands[i] = commands.back();
					commands.pop_back();
				}
			}
		}
	}


}

void InputManager::HandleInput()
{
	// Controller
	for (const auto& [button, commands] : m_ControllerCommands)
	{
		for (Command* pCommand : commands)
		{
			switch (pCommand->GetButtonAction())
			{
			case ButtonActionType::IsDown:
				if (IsDown(button, pCommand->GetControllerIndex()))
					pCommand->Execute();
				break;
			case ButtonActionType::IsPressed:
				if (IsPressed(button, pCommand->GetControllerIndex()))
					pCommand->Execute();
				break;
			case ButtonActionType::IsReleased:
				if (IsUp(button, pCommand->GetControllerIndex()))
					pCommand->Execute();
				break;
			}
		}
	}

	// Keyboard
	for (const auto& [button, commands] : m_KeyCommands)
	{
		for (Command* pCommand : commands)
		{
			switch (pCommand->GetButtonAction())
			{
			case ButtonActionType::IsDown:
				if (IsDown(button))
					pCommand->Execute();
				break;
			case ButtonActionType::IsPressed:
				if (IsPressed(button))
					pCommand->Execute();
				break;
			case ButtonActionType::IsReleased:
				if (IsUp(button))
					pCommand->Execute();
				break;
			}
		}
	}

}
bool InputManager::ProcessInput()
{
	m_pInputManager->ProcessInput();

	// Reset previous frame
	for (auto& [button, key] : m_Keys)
	{
		key.isPressed = false;
		key.isReleased = false;
	}

	m_MouseState.isPressed = false;
	m_MouseState.isReleased = false;

	// Poll Events
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			m_Keys[(char)e.key.keysym.sym] = KeyInput{ true, true, false };
		}
		else if (e.type == SDL_KEYUP)
		{
			m_Keys[(char)e.key.keysym.sym] = KeyInput{ false, false, true };
		}
		else if (e.type == SDL_MOUSEMOTION)
		{
			m_MouseState.position = { e.motion.x, RENDERER.GetWindowSize().y - e.motion.y };
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
			m_MouseState.isDown = true;
			m_MouseState.isPressed = true;
			
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				m_MouseState.button = MouseButton::LMB;
			}
			else if (e.button.button == SDL_BUTTON_RIGHT)
				m_MouseState.button = MouseButton::RMB;
			else
				m_MouseState.button = MouseButton::MMB;
		}
		else if (e.type == SDL_MOUSEBUTTONUP) 
		{
			m_MouseState.isDown = false;
			m_MouseState.isReleased = true;
			//m_MouseState.button = MouseButton::None; This had to be removed for the GetMouseButtonUp call
		}

		// ImGui Process Events
		GUI.HandleInput(&e);
	}

	return true;
}

bool InputManager::IsPressed(ControllerButton button, int controllerIndex) const
{
	return m_pInputManager->IsPressed(button, controllerIndex);
}
bool InputManager::IsDown(ControllerButton button, int controllerIndex) const
{
	return m_pInputManager->IsDown(button, controllerIndex);
}
bool InputManager::IsUp(ControllerButton button, int controllerIndex) const
{
	return m_pInputManager->IsUp(button, controllerIndex);
}

bool InputManager::IsPressed(char sdlKey)
{
	return m_Keys[(char)sdlKey].isPressed;
}
bool InputManager::IsDown(char sdlKey)
{
	return m_Keys[(char)sdlKey].isDown;
}
bool InputManager::IsUp(char sdlKey)
{
	return m_Keys[(char)sdlKey].isReleased;
}

bool InputManager::GetMouseButton(MouseButton index)
{
	return m_MouseState.button == index && m_MouseState.isDown;
}
bool InputManager::GetMouseButtonPressed(MouseButton index)
{
	return m_MouseState.button == index && m_MouseState.isPressed;
}
bool InputManager::GetMouseButtonUp(MouseButton index)
{
	return m_MouseState.button == index && m_MouseState.isReleased;
}
std::vector<char> InputManager::GetKeysPressedThisFrame() const
{
	std::vector<char> charsDown;

	for (auto& [key, keyInput] : m_Keys)
	{
		if (keyInput.isPressed)
			charsDown.push_back(key);
	}

	return charsDown;
}
#pragma endregion

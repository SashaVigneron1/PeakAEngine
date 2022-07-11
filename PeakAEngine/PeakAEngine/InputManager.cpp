#include "PeakAEnginePCH.h"
#include "InputManager.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <Xinput.h>
#include <SDL.h>

#include "GUIManager.h"

#pragma comment(lib, "XInput.lib")

//ToDo: Test
//ToDo: Add Commands
//ToDo: Enable warnings as errors again


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

	/*for (const auto& [button, commands] : m_ControllerCommands)
	{
		for (Command* pCommand : commands) delete pCommand;
	}*/
}

void InputManager::AddCommand(ControllerButton /*button*/, Command* /*pCommand*/, int /*controllerIndex*/)
{
	/*pCommand->SetControllerIndex(controllerIndex);
	m_ControllerCommands[button].push_back(pCommand);*/
}
void InputManager::AddCommand(char sdlKey, Command* pCommand)
{
	m_KeyCommands[sdlKey].push_back(pCommand);
}

void InputManager::RemoveCommand(Command* /*pCommand*/)
{

	/*if (m_ControllerCommands.size() > 0)
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
	}*/


}

void InputManager::HandleInput()
{
	// Controller
	//for (const auto& [button, commands] : m_ControllerCommands)
	//{
	//	// Could serve as a potential optimization, but also as a pessimization depending on the size of the vector
	//	/*if (IsPressed(button))
	//	{*/
	//	for (Command* pCommand : commands)
	//	{
	//		if (IsPressed(button, pCommand->GetControllerIndex()))
	//		{
	//			pCommand->Execute();
	//		}
	//	}
	//	//}
	//}

	//// Keyboard
	//for (const auto& [button, commands] : m_KeyCommands)
	//{
	//	for (Command* pCommand : commands)
	//	{
	//		if (IsPressed(button))
	//		{
	//			pCommand->Execute();
	//		}
	//	}
	//}

}
bool InputManager::ProcessInput()
{
	m_pInputManager->ProcessInput();

	for (auto& [button, key] : m_Keys)
	{
		key.isPressed = false;
		key.isReleased = false;
	}

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
		else if (e.type == SDL_MOUSEBUTTONDOWN) 
		{

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
#pragma endregion

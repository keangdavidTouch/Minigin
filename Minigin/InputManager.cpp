#include "MiniginPCH.h"
#include "InputManager.h"
#pragma comment(lib, "User32.lib")

kd::InputManager::InputManager()
{
	//ZeroMemory(&m_ConnectedController, sizeof(bool) * XUSER_MAX_COUNT);
	//ZeroMemory(&m_ThumbStickPosition, sizeof(glm::vec2) * XUSER_MAX_COUNT);

	m_pKeyboardState0 = new BYTE[256];
	m_pKeyboardState1 = new BYTE[256];
	ZeroMemory(m_pKeyboardState0, sizeof(BYTE) * 256);
	ZeroMemory(m_pKeyboardState1, sizeof(BYTE) * 256);
	GetKeyboardState(m_pKeyboardState0);
	GetKeyboardState(m_pKeyboardState1);
	
	m_KeyboardState0Active = true;
}

kd::InputManager::~InputManager()
{
	for (auto command : m_InputActions)
		SafeDelete(command.second);

	if(m_pKeyboardState0 != nullptr)
	{
		delete [] m_pKeyboardState0;
		delete [] m_pKeyboardState1;
	}
}

void kd::InputManager::ProcessInput()
{
	UpdateGameState();
	UpdateKeyboardState();

	for (auto action : m_InputActions)
	{
		auto currCommand = action.second->Command;

		switch(action.second->TriggerState)
		{
		case TriggerState::Pressed:
			if (IsGamePadPressed(int(action.second->ControllerButton), int(action.second->ControllerIndex)))
			{
				if (currCommand) currCommand->Execute(); 
			}

			if(IsKeyboardPressed(action.second->KeyboardCode))
			{
				if (currCommand) currCommand->Execute(); 
			}

			break;
		case TriggerState::Down:
			if (IsGamePadDown(int(action.second->ControllerButton), int(action.second->ControllerIndex)))
			{
				if (currCommand) currCommand->Execute(); 
			}

			if(IsKeyboardDown(action.second->KeyboardCode))
			{
				if (currCommand) currCommand->Execute(); 
			}

			break;
		case TriggerState::Released:
			if (IsGamePadRelease(int(action.second->ControllerButton), int(action.second->ControllerIndex)))
			{
				if (currCommand) currCommand->Execute(); 
			}

			if(IsKeyboardRelease(action.second->KeyboardCode))
			{
				if (currCommand) currCommand->Execute(); 
			}

			break;
		case TriggerState::LeftThumbStick:
			if (GetThumbstickPosition(true, int(action.second->ControllerIndex)) != glm::vec2(0, 0))
				if (currCommand) 
					currCommand->Execute();

			break;
		case TriggerState::RightThumbStick:
			if (GetThumbstickPosition(false, int(action.second->ControllerIndex)) != glm::vec2(0, 0))
				if (currCommand) 
					currCommand->Execute();

			break;
		}
	}
}

bool kd::InputManager::IsGamePadPressed(int button, int playerIndex) const
{
	if (!(m_ConnectedController[playerIndex] && button >= 0)) return false;

	return (m_CurrentInputStates[playerIndex].Gamepad.wButtons & button) != 0 && (m_PreviousInputStates[playerIndex].Gamepad.wButtons & button) == 0;
}

bool kd::InputManager::IsGamePadDown(int button, int playerIndex) const
{
	if (!(m_ConnectedController[playerIndex] && button >= 0)) return false;

	return (m_CurrentInputStates[playerIndex].Gamepad.wButtons & button) != 0 && (m_PreviousInputStates[playerIndex].Gamepad.wButtons & button) != 0;
}

bool kd::InputManager::IsGamePadRelease(int button, int playerIndex) const
{
	if (!(m_ConnectedController[playerIndex] && button >= 0)) return false;

	return (m_CurrentInputStates[playerIndex].Gamepad.wButtons & button) == 0 && (m_PreviousInputStates[playerIndex].Gamepad.wButtons & button) != 0;
}

glm::vec2 kd::InputManager::GetThumbstickPosition(bool leftStick, int playerIndex) const
{
	 glm::vec2 vec(0, 0);

	if (!m_ConnectedController[playerIndex]) return vec;

	if (leftStick)
	{
		vec.x = fmaxf(-1, float(m_CurrentInputStates[playerIndex].Gamepad.sThumbLX) / SHRT_MAX);
		vec.y = -fmaxf(-1, float(m_CurrentInputStates[playerIndex].Gamepad.sThumbLY) / SHRT_MAX);
	}
	else
	{
		vec.x = fmaxf(-1, float(m_CurrentInputStates[playerIndex].Gamepad.sThumbRX) / SHRT_MAX);
		vec.y = -fmaxf(-1, float(m_CurrentInputStates[playerIndex].Gamepad.sThumbRY) / SHRT_MAX);
	}

	return vec;
}

bool kd::InputManager::IsKeyboardPressed(int key)
{
	if (!(key > 0x07 && key <= 0xFE)) return false;
	return (m_pCurrKeyboardState[key]&0xF0) != 0 && (m_pOldKeyboardState[key]&0xF0) == 0;
}

bool kd::InputManager::IsKeyboardDown(int key)
{
	if (!(key > 0x07 && key <= 0xFE)) return false;
	return (m_pCurrKeyboardState[key]&0xF0) != 0 && (m_pOldKeyboardState[key]&0xF0) != 0;
}

bool kd::InputManager::IsKeyboardRelease(int key)
{
	if (!(key > 0x07 && key <= 0xFE)) return false;
	return (m_pCurrKeyboardState[key]&0xF0) == 0 && (m_pOldKeyboardState[key]&0xF0) != 0;
}

void kd::InputManager::RegisterAction(int id, std::shared_ptr<BaseCommand> command, int keyCode, CtrlButton controllerButton,
	CIndex controllerIndex, TriggerState state)
{
	if (m_InputActions[id] == nullptr)
	{
		m_InputActions[id] = new InputAction(command, keyCode, controllerButton, controllerIndex, state);
	}
	else
	{
		std::cout << "\033[33m" << "LOG:: InputAction with id " << id << " is already existed" << std::endl;
	}
}

void kd::InputManager::UpdateGameState()
{
	for (int i = 0; i < XUSER_MAX_COUNT; i++)
	{
		// Set Previous State
		m_PreviousInputStates[i] = m_CurrentInputStates[i];

		// Zeroise the state
		ZeroMemory(&m_CurrentInputStates[i], sizeof(XINPUT_STATE));

		//Input State Result
		DWORD dwResult;

		// Get Current state
		dwResult = XInputGetState(i, &m_CurrentInputStates[i]);

		m_ConnectedController[i] = (dwResult == ERROR_SUCCESS); // Controller is connected 
	}
}

void kd::InputManager::UpdateKeyboardState()
{
	BOOL getKeyboardResult;
	if(m_KeyboardState0Active)
	{
		getKeyboardResult = GetKeyboardState(m_pKeyboardState1);
		m_pOldKeyboardState = m_pKeyboardState0;
		m_pCurrKeyboardState = m_pKeyboardState1;
	}
	else
	{
		getKeyboardResult = GetKeyboardState(m_pKeyboardState0);
		m_pOldKeyboardState = m_pKeyboardState1;
		m_pCurrKeyboardState = m_pKeyboardState0;
	}

	m_KeyboardState0Active = !m_KeyboardState0Active;

	//return getKeyboardResult > 0;
}

#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include <unordered_map>
#include "BaseCommand.h"
#include "Singleton.h"
#include <glm/vec2.hpp>
#pragma comment (lib, "xinput.lib") // the project must link against the XInput.lib
#pragma warning(pop)

namespace kd
{
	enum class TriggerState
	{
		Pressed, Down, Released, LeftThumbStick, RightThumbStick
	};

	enum class CIndex
	{
		One = 0,
		Two = 1,
		Three = 2,
		Four = 3,
	};

	enum class CtrlButton
	{
		None = -1,
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		ButtonUp = XINPUT_GAMEPAD_DPAD_UP,
		ButtonDown = XINPUT_GAMEPAD_DPAD_DOWN,
		ButtonLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		ButtonRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		ButtonStart = XINPUT_GAMEPAD_START,
		ButtonBack = XINPUT_GAMEPAD_BACK,
		LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		RightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB
	};

	struct InputAction
	{
		InputAction(std::shared_ptr<BaseCommand> command, int keyCode, CtrlButton controllerButton, CIndex controllerIndex, TriggerState state) :
			Command(command),
			KeyboardCode(keyCode),
			ControllerButton(controllerButton),
			ControllerIndex(controllerIndex),
			TriggerState(state) {}

		~InputAction(){}

		std::shared_ptr<BaseCommand> Command;
		int KeyboardCode;
		CtrlButton ControllerButton;
		CIndex ControllerIndex;
		TriggerState TriggerState;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		void ProcessInput();
		bool IsGamePadPressed(int button, int playerIndex) const;
		bool IsGamePadDown(int button, int playerIndex) const;
		bool IsGamePadRelease(int button, int playerIndex) const;
		glm::vec2 GetThumbstickPosition(bool leftStick = true, int playerIndex = 0) const;
		bool IsKeyboardPressed(int key);
		bool IsKeyboardDown(int key);
		bool IsKeyboardRelease(int key);
		void RegisterAction(int id, std::shared_ptr<BaseCommand> command, int keyCode, CtrlButton controllerButton, CIndex controllerIndex, TriggerState state);
	private:
		XINPUT_STATE m_CurrentInputStates[XUSER_MAX_COUNT]{};
		XINPUT_STATE m_PreviousInputStates[XUSER_MAX_COUNT]{};
		bool m_ConnectedController[XUSER_MAX_COUNT];
		glm::vec2 m_ThumbStickPosition[XUSER_MAX_COUNT];

		BYTE *m_pCurrKeyboardState, *m_pOldKeyboardState, *m_pKeyboardState0, *m_pKeyboardState1;
		bool m_KeyboardState0Active;
		std::unordered_map<int, InputAction*> m_InputActions;

		void UpdateGameState();
		void UpdateKeyboardState();
	};
}
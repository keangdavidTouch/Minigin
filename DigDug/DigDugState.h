#pragma once
#include "InputManager.h"
#include "GameObject.h"
#include "SpriteComponent.h"

namespace kd
{
	class BaseState
	{
	public:
		virtual BaseState* HandleInput(GameObject* object, const InputAction* input) = 0;
		virtual void Update(GameObject* object) = 0;
		virtual void Enter(GameObject* object) = 0;
		virtual void Exit(GameObject* object) = 0;
	};
};

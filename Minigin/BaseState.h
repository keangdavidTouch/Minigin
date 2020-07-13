#pragma once
#include "GameObject.h"

namespace kd
{
	class BaseState
	{
	public:
		virtual ~BaseState() = default;
		virtual BaseState* Update(GameObject* object) = 0;
		virtual void Enter(GameObject* object) = 0;
		virtual void Exit(GameObject* object) = 0;
	};
};

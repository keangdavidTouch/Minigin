#pragma once
#include "BaseState.h"

namespace kd {

	class WanderState : public BaseState
	{
	public:
		WanderState() = default;
		~WanderState() = default;
		BaseState* HandleInput(GameObject* object, const BaseCommand* command);
		void Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	};
}
#pragma once
#include "BaseState.h"

namespace kd {

	class SpriteComponent;
	class RockBehaviour;

	class RockIdleState : public BaseState
	{
	public:
		RockIdleState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	private:
		float m_RockCrackElapsedSec = 0.0f;
		SpriteComponent* m_Sprite;
	};

	class RockCrackState : public BaseState
	{
	public:
		RockCrackState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	private:
		float m_FallSpeed = 200.f;
		float m_CrackDuration = 0.5f;
		float m_CrackElapedSec;
		SpriteComponent* m_Sprite;
		RockBehaviour* m_Behaviour;
	};
}


#pragma once
#include "BaseState.h"

namespace kd {
	class AIComponent;
	class SpriteComponent;
	class FygarBehaviour;
	class EnemyBehaviour;

	class WanderState : public BaseState
	{
	public:
		WanderState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	private:
		float m_WanderElapsedSec = 0.0f;
		const float m_WanderTime = 5.0f;
		AIComponent* m_AIComponent;
		EnemyBehaviour* m_EnemyBehaviour;
	};


	class ChaseState : public BaseState
	{
	public:
		ChaseState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	private:
		EnemyBehaviour* m_EnemyBehaviour;
	};


	class GhostState : public BaseState
	{
	public:
		GhostState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	private:
		GameObject* m_Target = nullptr;
		AIComponent* m_AIComponent;
		const float m_Speed = 35.f;
	};


	class GetPumpedState : public BaseState
	{
	public:
		GetPumpedState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	private:
		float m_PumpElapsedSec = 0.f;
		const float m_PumpMidDuration = 1.25f;
		const float m_PumpDuration = 2.f;
		SpriteComponent* m_Sprite;
		EnemyBehaviour* m_EnemyBehaviour;
	};


	class FygarFireState : public BaseState
	{
	public:
		FygarFireState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	private:
		float m_FireElapsedSec = 0.f;
		const float m_FireDuration = 1.f;
		FygarBehaviour* m_Component;
	};
	

	class EnemyDieState : public BaseState
	{
	public:
		EnemyDieState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	private:
		float m_DyingElapsedSec = 0.f;
		const float m_DyingDuration = 1.f;
	};
}
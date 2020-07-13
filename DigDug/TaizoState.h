#pragma once
#include "BaseState.h"
#include "DigDugGame.h"

namespace kd {

	class TaizoBehaviour;
	class SpriteComponent;

	class IdleState final : public BaseState
	{
	public:
		IdleState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	private:
		TaizoBehaviour* m_Behaviour;
	};

	class RunState final : public BaseState
	{
	public:
		RunState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	private:
		TaizoBehaviour* m_Behaviour;
	};

	class PumpState final : public BaseState
	{
	public:
		PumpState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;
	private:
		bool m_Finish = false;
		float m_PumpElapsedSec = 0.0f;
		const float m_PumpDuration = 1.0f;
		const float m_PumpSpeed = 100.f;
		TaizoBehaviour* m_Behaviour;
		SpriteComponent* m_Sprite;
	};

	class DieState final : public BaseState
	{
	public:
		DieState() = default;
		BaseState* Update(GameObject* object) override;
		void Enter(GameObject* object) override;
		void Exit(GameObject* object) override;

	private:
		float m_DyingElapsedSec = 0.f;
		const float m_DyingDuration = 1.0f;
		SpriteComponent* m_Sprite;
	};
}
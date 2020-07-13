#pragma once
#include "BaseComponent.h"
#include "EnemyBehaviour.h"
#include "DigDugPrefabs.h"

namespace kd
{
	class BaseState;
	class BaseCommand;
	class StateMachine;
	
	class TaizoBehaviour final : public BaseComponent 
	{

	public:

		friend class HealthDisplay;
		friend class ScoreDisplay;

		enum class MoveDirection { Left, Right, Up, Down };
		enum EventType { Pumping, Digging, RockEnemy, Death };
		enum Animation { Idle, Run, Dig, Shoot, Pump, Die };

		TaizoBehaviour(GameObject* pumpObject, float speed = 1); 
		~TaizoBehaviour();

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void TriggerEnter(CollisionHit* hit);
		
		void SetDead(bool dead) { m_IsDead = dead; };
		const bool IsDead() const { return m_IsDead; }
		void SetMove(bool move) { m_IsMoving = move; };
		const bool IsMoving() { return m_IsMoving; };
		void SetPump(bool enable) { m_IsPumping = enable; }
		const bool IsPumping() { return m_IsPumping; }

		const float GetSpeed() { return m_Speed; }
		void ReleaseEnemy() { m_IsAttackingEnemy = false; };
		void SetEnemy(EnemyBehaviour::Type type) { m_IsAttackingEnemy = true; m_EnemyType = type; };
		bool IsAttackingEnemy() const { return m_IsAttackingEnemy; }
		bool IsEnemy(GameObject* object);
		
		void Reset();
		GameObject* GetWeapon() const { return  m_PumpWeapon; };

	private:
		int m_Score = 0;
		int m_Life = 3;
		float m_Speed = 2;
		bool m_IsPumping = false;
		bool m_IsMoving = false;
		bool m_IsDead = false;
		bool m_IsAttackingEnemy = false;
		EnemyBehaviour::Type m_EnemyType;
		GameObject* m_PumpWeapon;
		StateMachine* m_StateMachine;
	};
}


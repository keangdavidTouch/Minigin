#pragma once
#include "BaseComponent.h"
#include "SpriteComponent.h"

namespace kd
{
	class StateMachine;
	struct CollisionHit;

	class EnemyBehaviour : public BaseComponent 
	{
	public:

		enum class Type { Pooka = 1, Fygar = 2 };
		enum class AttackState { None, Fire };
		enum Animation { Bounce, Crush, Ghost, Bloat, Explode };

		EnemyBehaviour(GameObject* player, SpriteInfo&& dyingSprite); 
		virtual ~EnemyBehaviour();

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void TriggerEnter(CollisionHit* hit);
		virtual void HandleAttack();
		void SetAttackState(AttackState attack) { m_AttackState = attack; };
		AttackState GetAttackState() const { return m_AttackState; };
		bool GetPumped() const { return m_GetPumped; };
		void SetGetPumped(bool pump) { m_GetPumped = pump; };
		SpriteInfo& GetDyingSpriteInfo() { return m_DyingSpriteInfo; };
		SpriteInfo& GetNormalSpriteInfo() { return m_SpriteInfo; };
		bool GetRocked() const { return m_GetRocked; }

	protected:
		bool m_GetRocked;
		bool m_GetPumped;
		AttackState m_AttackState;
		SpriteInfo m_DyingSpriteInfo;
		SpriteInfo m_SpriteInfo;
		SpriteComponent* m_Sprite;
		GameObject* m_Player;
		StateMachine* m_StateMachine;
	};
}


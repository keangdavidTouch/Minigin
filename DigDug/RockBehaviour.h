#pragma once
#include "BaseComponent.h"

namespace kd
{
	class StateMachine;
	class DigTileComponent;
	struct CollisionHit;

	class RockBehaviour final : public BaseComponent
	{
	public:

		enum Animation { Idle, Shake, Crack };

		RockBehaviour();
		~RockBehaviour();

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void TriggerEnter(CollisionHit* hit);
		bool ShouldFall() const { return m_ShouldFall; };
		bool IsFalling() { return m_IsFalling; };
		void SetFalling(bool fall) { m_IsFalling = fall; }
		GameObject* GetTriggerObject() { return m_TriggerObject; };
		void UpdateScore(GameObject* player);
	private:
		StateMachine* m_StateMachine;
		bool m_IsFalling = false;
		bool m_ShouldFall = false;
		GameObject* m_TriggerObject = nullptr; 
		DigTileComponent* m_OccupiedTile = nullptr;
	};
}



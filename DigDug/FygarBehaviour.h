#pragma once
#include "EnemyBehaviour.h"

namespace kd
{
	class FygarBehaviour final : public EnemyBehaviour 
	{
	public:
		FygarBehaviour(GameObject* fire, GameObject* player); 
		~FygarBehaviour();
		void AddFlame();
		void RemoveFlame();
		void HandleAttack() override;
	private:
		GameObject* m_Flame;
	};
}

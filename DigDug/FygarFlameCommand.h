#include "BaseCommand.h"
#include "GameObject.h"
#include "FygarBehaviour.h"

namespace kd
{
	class FygarFlameCommand final : public BaseCommand
	{
	public:

		FygarFlameCommand(GameObject* player) : m_Player(player)
		{
			m_Behaviour = player->GetComponent<FygarBehaviour>();
		}

		void Execute() override {
			m_Behaviour->SetAttackState(EnemyBehaviour::AttackState::Fire);
		}

	private:
		GameObject* m_Player;
		FygarBehaviour* m_Behaviour;
	};
}

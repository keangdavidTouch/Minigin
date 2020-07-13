#include "BaseCommand.h"
#include "GameObject.h"
#include "TaizoBehaviour.h"

namespace kd
{
	class PumpCommand final : public BaseCommand
	{
	public:

		PumpCommand(GameObject* player) : m_Player(player)
		{
			m_Behaviour = player->GetComponent<TaizoBehaviour>();
		}

		void Execute() override {
			m_Behaviour->SetPump(true);
		}

	private:
		GameObject* m_Player;
		TaizoBehaviour* m_Behaviour;
	};
}

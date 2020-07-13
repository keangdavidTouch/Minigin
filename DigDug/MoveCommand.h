#include "BaseCommand.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "TaizoBehaviour.h"

namespace kd
{
	class MoveCommand final : public BaseCommand
	{
	public:

		MoveCommand(GameObject* player, TaizoBehaviour::MoveDirection direction) : m_Direction(direction),  m_Player(player)
		{
			m_Behaviour = player->GetComponent<TaizoBehaviour>();
			if(m_Behaviour) m_MoveSpeed = m_Behaviour->GetSpeed();
		}

		void Execute() override {

			if(m_Behaviour->IsDead())
				return;

			// Use WasMove to Avoid Diagonal Move
			if(m_Behaviour->IsMoving())
				return;

			auto pos = m_Player->GetTransform().GetPosition();

			// Reset Sprite Flip/Rotation First
			m_Player->GetTransform().SetFlip(Transform::Flip::None);
			m_Player->GetTransform().SetRotation(0);

			// Snap to Grid
			auto gridSize = DigDugGame::GetGameContext().GridSize;

			switch (m_Direction)
			{
			case TaizoBehaviour::MoveDirection::Left:
				m_Player->GetTransform().SetFlip(Transform::Flip::Vertical);
				m_Player->GetTransform().SetRotation(180);
				pos.x -= m_MoveSpeed;
				pos.y = glm::round(pos.y / gridSize) * gridSize;
				m_Behaviour->SetMove(true);
				break;
			case TaizoBehaviour::MoveDirection::Right:
				pos.x += m_MoveSpeed;
				pos.y = glm::round(pos.y / gridSize) * gridSize;
				m_Behaviour->SetMove(true);
				break;
			case TaizoBehaviour::MoveDirection::Up:
				m_Player->GetTransform().SetRotation(-90);
				pos.y -= m_MoveSpeed;
				pos.x = glm::round(pos.x / gridSize) * gridSize;
				m_Behaviour->SetMove(true);
				break;
			case TaizoBehaviour::MoveDirection::Down:
				m_Player->GetTransform().SetRotation(90);
				pos.y += m_MoveSpeed;
				pos.x = glm::round(pos.x / gridSize) * gridSize;
				m_Behaviour->SetMove(true);
				break;
			}

			const auto boundary = DigDugGame::GetGameContext().Boundary;
			pos.x = glm::clamp(pos.x, boundary.MinX, boundary.MaxX);
			pos.y = glm::clamp(pos.y, boundary.MinY, boundary.MaxY);

			m_Player->GetTransform().SetPosition(pos);
		}

	private:
		float m_MoveSpeed = 1.0f;
		TaizoBehaviour::MoveDirection m_Direction;
		GameObject* m_Player;
		TaizoBehaviour* m_Behaviour;
	};
}

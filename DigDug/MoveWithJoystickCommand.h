#include "BaseCommand.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteComponent.h"
#include "DigDugGame.h"

namespace kd
{
	class MoveWithJoyStickCommand final : public BaseCommand
	{
	public:

		MoveWithJoyStickCommand(GameObject* player, float speed, bool leftStick = true, int controllerIndex = 0) 
			: m_Player(player), m_MoveSpeed(speed), m_LeftThumbStick(leftStick), m_ControllerIndex(controllerIndex)
		{
			m_Sprite = player->GetComponent<SpriteComponent>();
		}

		void Execute() override {

			auto pos = m_Player->GetTransform().GetPosition();
			const auto thumbStickPos = InputManager::GetInstance().GetThumbstickPosition(m_LeftThumbStick, m_ControllerIndex);

			const bool shouldMoveX = abs(thumbStickPos.x) > abs(thumbStickPos.y);

			// Snap to Grid
			auto gridSize = DigDugGame::GetGameContext().GridSize;

			if (shouldMoveX)
			{
				if (thumbStickPos.x > 0)
			{
					UpdateTransform(0, Transform::Flip::None);
					pos.x += m_MoveSpeed;
					pos.y = glm::round(pos.y / gridSize) * gridSize;

				}
				else if (thumbStickPos.x < 0)
				{
					UpdateTransform(180, Transform::Flip::Vertical);
					pos.x -= m_MoveSpeed;
					pos.y = glm::round(pos.y / gridSize) * gridSize;
				}
			}
			else
			{
				if (thumbStickPos.y > 0)
				{
					UpdateTransform(90, Transform::Flip::None);
					pos.y += m_MoveSpeed;
					pos.x = glm::round(pos.x / gridSize) * gridSize;
				}
				else if (thumbStickPos.y < 0)
				{
					UpdateTransform(-90, Transform::Flip::None);
					pos.y -= m_MoveSpeed;
					pos.x = glm::round(pos.x / gridSize) * gridSize;
				}
			}

			const auto boundary = DigDugGame::GetGameContext().Boundary;
			pos.x = glm::clamp(pos.x, boundary.MinX, boundary.MaxX);
			pos.y = glm::clamp(pos.y, boundary.MinY, boundary.MaxY);

			m_Player->GetTransform().SetPosition(pos);
		}

	private:
		GameObject* m_Player;
		SpriteComponent* m_Sprite;
		int m_ControllerIndex = 0;
		bool m_LeftThumbStick = true;
		float m_MoveSpeed = 1.0f;
		
		void UpdateTransform(float angle, Transform::Flip flip)
		{
			m_Player->GetTransform().SetFlip(flip);
			m_Player->GetTransform().SetRotation(angle);
		}
	};
}


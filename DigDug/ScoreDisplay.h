#pragma once
#include "Observer.h"
#include "Subject.h"
#include "DigDugGame.h"

namespace kd
{
	class GameObject;

	class ScoreDisplay : public Observer
	{
	public:
		ScoreDisplay(GameObject* textObject);
		~ScoreDisplay() = default;
		void OnNotify(int event, GameObject* object) override;

	private:
		int GetScoreBaseOnLayer(int posY);

		const float m_GridSize = DigDugGame::GetGameContext().GridSize;
		const float m_Layer1 = m_GridSize * 2;
		const float m_Layer2 = m_GridSize * 5;
		const float m_Layer3 = m_GridSize * 8;
		const float m_Layer4 = m_GridSize * 12;
		Subject m_Subject;
		GameObject* m_TextObject;
	};
}


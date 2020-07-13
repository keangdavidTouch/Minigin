#include "pch.h"
#include "ScoreDisplay.h"
#include "GameObject.h"
#include "TaizoBehaviour.h"
#include "TextComponent.h"

kd::ScoreDisplay::ScoreDisplay(GameObject* textObject) : m_TextObject(textObject)
{
}

void kd::ScoreDisplay::OnNotify(int event, GameObject* object)
{
	if(event == TaizoBehaviour::EventType::Pumping)
	{
		auto taizo = object->GetComponent<TaizoBehaviour>();
		const auto pumpScore = int(taizo->m_EnemyType) * GetScoreBaseOnLayer(int(object->GetTransform().GetPosition().y));
		taizo->m_Score += pumpScore;
		m_TextObject->GetComponent<TextComponent>()->SetText(std::to_string(taizo->m_Score));
	}
	else if(event == TaizoBehaviour::EventType::RockEnemy)
	{
		auto taizo = object->GetComponent<TaizoBehaviour>();
		taizo->m_Score += 1000;
		m_TextObject->GetComponent<TextComponent>()->SetText(std::to_string(taizo->m_Score));
	}
}

int kd::ScoreDisplay::GetScoreBaseOnLayer(int posY)
{
	if(posY >= m_Layer4) {
		return 500;
	}
	else if(posY >= m_Layer3) {
		return 400;
	}
	else if(posY >= m_Layer2) {
		return 300;
	}
	else if(posY >= m_Layer1) {
		return 200;
	}

	return 0;
}

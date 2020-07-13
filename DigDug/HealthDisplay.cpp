#include "pch.h"
#include "HealthDisplay.h"
#include "TaizoBehaviour.h"
#include "TextComponent.h"

kd::HealthDisplay::HealthDisplay(GameObject* textObject) : m_TextObject(textObject)
{
}

void kd::HealthDisplay::OnNotify(int event, GameObject* object)
{
	switch(event)
	{
	case TaizoBehaviour::EventType::Death:
		auto taizo = object->GetComponent<TaizoBehaviour>();
		if(taizo->m_Life > 0) {
			taizo->m_Life -= 1;
			m_TextObject->GetComponent<TextComponent>()->SetText("LIFE " + std::to_string(taizo->m_Life));
		}
		break;
	}
}

#include "pch.h"
#include "Time.h"
#include "DigDugGame.h"
#include "RockState.h"
#include "RockBehaviour.h"
#include "TaizoBehaviour.h"
#include "SpriteComponent.h"

kd::BaseState*  kd::RockIdleState::Update(GameObject* object)
{
	if (object->GetComponent<RockBehaviour>()->ShouldFall())
	{
		if(m_Sprite) m_Sprite->SetCurrentClip(RockBehaviour::Animation::Shake);
		m_RockCrackElapsedSec += Time::GetInstance().DeltaTime();
	}

	if (m_RockCrackElapsedSec >= 1.5f)
		return new RockCrackState();
	
	return nullptr;
}

void kd::RockIdleState::Enter(GameObject* object)
{
	m_Sprite = object->GetComponent<SpriteComponent>();
	std::cout << "Enter Rock-IdleState" << std::endl;
}

void kd::RockIdleState::Exit(GameObject* object)
{
	object->GetComponent<RockBehaviour>()->SetFalling(true);
}


kd::BaseState* kd::RockCrackState::Update(GameObject* object)
{
	auto pos = object->GetTransform().GetPosition();
	pos.y += m_FallSpeed * Time::GetInstance().DeltaTime();
	
	m_Behaviour->SetFalling(true);

	if(m_Behaviour->ShouldFall())
	{
		object->GetTransform().SetPosition(pos.x, pos.y, pos.z);
	}
	else
	{
		m_CrackElapedSec += Time::GetInstance().DeltaTime();

		if(m_CrackElapedSec > m_CrackDuration)
		{
			SceneManager::GetInstance().GetActiveScene()->RemoveGameObject(object);
			return nullptr;
		}

		if(!m_Sprite->SetCurrentClip(RockBehaviour::Animation::Crack))
		{
			m_Sprite->SetPause(true);
		}
	}

	return nullptr;
}

void kd::RockCrackState::Enter(GameObject* object)
{
	m_Behaviour = object->GetComponent<RockBehaviour>();
	m_Sprite = object->GetComponent<SpriteComponent>();
	std::cout << "Enter Rock-Crack State" << std::endl;
}

void kd::RockCrackState::Exit(GameObject*){}

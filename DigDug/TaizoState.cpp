#include "pch.h"
#include "Time.h"
#include "TaizoState.h"
#include "MoveCommand.h"
#include "PumpCommand.h"
#include "TaizoBehaviour.h"

#pragma region STATE_IDLE
kd::BaseState* kd::IdleState::Update(GameObject*)
{
	if(m_Behaviour->IsDead())
		return new DieState();

	if(m_Behaviour->IsMoving())
		return new RunState();

	if(m_Behaviour->IsPumping())
		return new PumpState();

	return nullptr;
}

void kd::IdleState::Enter(GameObject* object)
{
	m_Behaviour = object->GetComponent<TaizoBehaviour>();
	object->GetComponent<SpriteComponent>()->SetCurrentClip(TaizoBehaviour::Animation::Idle);
	std::cout << "Enter IdleState" << std::endl;
}

void kd::IdleState::Exit(GameObject* )
{
}
#pragma endregion

#pragma region STATE_RUN
kd::BaseState* kd::RunState::Update(GameObject*)
{
	if(m_Behaviour->IsDead())
		return new DieState();

	if(m_Behaviour->IsMoving() == false)
		return new IdleState();

	return nullptr;
}

void kd::RunState::Enter(GameObject* object)
{
	m_Behaviour = object->GetComponent<TaizoBehaviour>();
	object->GetComponent<SpriteComponent>()->SetCurrentClip(TaizoBehaviour::Animation::Dig);
	std::cout << "Enter Run State" << std::endl;
}

void kd::RunState::Exit(GameObject* )
{
}
#pragma endregion

#pragma region STATE_PUMP
kd::BaseState*  kd::PumpState::Update(GameObject*)
{
	if(m_Behaviour->IsPumping())
		m_PumpElapsedSec = 0;
	else if(m_Behaviour->IsMoving())
		return new RunState();

	if (m_Finish || m_PumpElapsedSec > m_PumpDuration)
		return new IdleState();

	m_PumpElapsedSec += Time::GetInstance().DeltaTime();

	if(m_Behaviour->IsAttackingEnemy())
	{
		m_Sprite->SetCurrentClip(TaizoBehaviour::Animation::Pump);
		return nullptr;
	}

	auto& weaponTransform = m_Behaviour->GetWeapon()->GetTransform();

	auto pos = weaponTransform.GetLocalPosition();
	pos.x += m_PumpSpeed * Time::GetInstance().DeltaTime();

	if (pos.x <= DigDugGame::GetGameContext().SpriteSize * 3)
		weaponTransform.SetLocalPosition(pos.x, pos.y, pos.z);
	else
		m_Finish = true;

	return nullptr;
}

void kd::PumpState::Enter(GameObject* object)
{
	m_Behaviour = object->GetComponent<TaizoBehaviour>();
	m_Sprite = object->GetComponent<SpriteComponent>();

	m_Sprite->SetCurrentClip(TaizoBehaviour::Animation::Shoot);
	object->AddChild(m_Behaviour->GetWeapon());
	std::cout << "Enter PumpState" << std::endl;
}

void kd::PumpState::Exit(GameObject* object)
{
	auto weapon = m_Behaviour->GetWeapon();
	weapon->GetTransform().SetLocalPosition(0,0,0);
	object->RemoveChild(weapon);
	if(m_PumpElapsedSec > m_PumpDuration)
	{
		object->GetSubject().Notify(int(TaizoBehaviour::EventType::Pumping), object);
	}
	m_Behaviour->ReleaseEnemy();
}
#pragma endregion

#pragma region STATE_DIE
kd::BaseState* kd::DieState::Update(GameObject*)
{
	if (m_DyingElapsedSec > m_DyingDuration)
	{
		return new IdleState();
	}

	m_DyingElapsedSec += Time::GetInstance().DeltaTime();

	return nullptr;
}

void kd::DieState::Enter(GameObject* object)
{
	m_Sprite = object->GetComponent<SpriteComponent>();
	m_Sprite->GetSpriteInfo().Rect.y = 16;
	m_Sprite->SetCurrentClip(TaizoBehaviour::Animation::Die);
	object->GetSubject().Notify(int(TaizoBehaviour::EventType::Death), object);
	std::cout << "Enter DyingState" << std::endl;
}

void kd::DieState::Exit(GameObject* object)
{
	m_Sprite->GetSpriteInfo().Rect.y = 0;
	m_Sprite->SetCurrentClip(TaizoBehaviour::Animation::Idle);
	object->GetComponent<TaizoBehaviour>()->Reset();
}
#pragma endregion
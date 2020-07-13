#include "pch.h"
#include "EnemyState.h"
#include "Time.h"
#include <iostream>
#include "FygarFlameCommand.h"
#include "MoveWithJoystickCommand.h"
#include "PoogaBehaviour.h"
#include "FygarBehaviour.h"
#include "AIComponent.h"

#pragma region STATE_WANDER
void kd::WanderState::Enter(GameObject* object)
{
	m_EnemyBehaviour = object->GetComponent<EnemyBehaviour>();
	m_AIComponent = object->GetComponent<AIComponent>();
	object->GetComponent<SpriteComponent>()->SetCurrentClip(EnemyBehaviour::Animation::Bounce);
	//auto m_Sprite = object->GetComponent<SpriteComponent>();
	//m_Sprite->SetSpriteInfo(m_EnemyBehaviour->GetDyingSpriteInfo(), EnemyBehaviour::Animation::Explode);
	std::cout << "Enter Enemy-IdleState" << std::endl;
}

kd::BaseState* kd::WanderState::Update(GameObject*)
{
	m_WanderElapsedSec += Time::GetInstance().DeltaTime();

	if (m_WanderElapsedSec > m_WanderTime)
	{
		if (m_AIComponent->NoAvailablePath()) {
			return new GhostState();
		}
		else {
			return new ChaseState();
		}
	}
	
	if (m_EnemyBehaviour->GetPumped()) {
		return new GetPumpedState();
	}
	else if (m_EnemyBehaviour->GetRocked()) {
		return new EnemyDieState();
	}

	return nullptr;
}

void kd::WanderState::Exit(GameObject* ){}
#pragma endregion

#pragma region STATE_GHOST
void kd::GhostState::Enter(GameObject* object)
{
	object->GetComponent<SpriteComponent>()->SetCurrentClip(EnemyBehaviour::Animation::Ghost);
	m_AIComponent = object->GetComponent<AIComponent>();
	m_Target = m_AIComponent->GetTarget();
	std::cout << "Enter Enemy-GhostState" << std::endl;
}

kd::BaseState* kd::GhostState::Update(GameObject* object)
{
	auto playerPos = object->GetTransform().GetPosition();
	auto targetPos = m_Target->GetTransform().GetPosition();
	
	auto speed = Time::GetInstance().DeltaTime() * m_Speed;
	auto direction = glm::normalize(targetPos - playerPos);
	playerPos += (direction * speed);

	object->GetTransform().SetPosition(playerPos);

	if(m_AIComponent->NoAvailablePath() == false) {
		return new ChaseState();
	}

	return nullptr;
}

void kd::GhostState::Exit(GameObject* ){}
#pragma endregion

#pragma region STATE_GETPUMPED
void kd::GetPumpedState::Enter(GameObject* object)
{
	m_EnemyBehaviour = object->GetComponent<EnemyBehaviour>();
	m_Sprite = object->GetComponent<SpriteComponent>();
	m_Sprite->ChangeSpriteInfo(m_EnemyBehaviour->GetDyingSpriteInfo(), EnemyBehaviour::Animation::Bloat);
	//m_Sprite->SetSpriteInfo(m_EnemyBehaviour->GetDyingSpriteInfo());
	//m_Sprite->SetCurrentClip(EnemyBehaviour::Animation::Bloat);
	std::cout << "Enter Enemy-ExplodeState" << std::endl;
}

kd::BaseState*  kd::GetPumpedState::Update(GameObject* object)
{
	m_PumpElapsedSec += Time::GetInstance().DeltaTime();

	if(m_PumpElapsedSec > m_PumpMidDuration) {
	
		m_Sprite->SetCurrentClip(EnemyBehaviour::Animation::Explode);

		if(m_PumpElapsedSec > m_PumpDuration) {
			SceneManager::GetInstance().GetActiveScene()->RemoveGameObject(object);
			return nullptr;
		}
	}
	else {
		if(m_EnemyBehaviour->GetPumped() == false) {
			return new WanderState();
		}
	}

	return nullptr;
}

void kd::GetPumpedState::Exit(GameObject*)
{
	m_Sprite->ChangeSpriteInfo(m_EnemyBehaviour->GetNormalSpriteInfo(), EnemyBehaviour::Animation::Bounce);
}

#pragma endregion

#pragma region STATE_CHASE
kd::BaseState* kd::ChaseState::Update(GameObject*)
{
	if (m_EnemyBehaviour->GetPumped()) {
		return new GetPumpedState();
	}
	else if (m_EnemyBehaviour->GetRocked()) {
		return new EnemyDieState();
	}

	m_EnemyBehaviour->HandleAttack();
	if (m_EnemyBehaviour->GetAttackState() == EnemyBehaviour::AttackState::Fire) {
		return new FygarFireState();
	}

	return nullptr;
}

void kd::ChaseState::Enter(GameObject* object)
{
	m_EnemyBehaviour = object->GetComponent<EnemyBehaviour>();
	object->GetComponent<SpriteComponent>()->SetCurrentClip(EnemyBehaviour::Animation::Bounce);
	object->GetComponent<AIComponent>()->SetEnable(true);
	std::cout << "Enter Enemy-ChaseState" << std::endl;
}

void kd::ChaseState::Exit(GameObject* object)
{
	object->GetComponent<AIComponent>()->SetEnable(false);
}
#pragma endregion

#pragma region STATE_FYGAFIRE
void kd::FygarFireState::Enter(GameObject* object)
{
	m_Component = object->GetComponent<FygarBehaviour>();
	m_Component->AddFlame();
	std::cout << "Enter Fygar-FireState" << std::endl;
}

kd::BaseState* kd::FygarFireState::Update(GameObject* )
{
	m_FireElapsedSec += Time::GetInstance().DeltaTime();

	if (m_FireElapsedSec > m_FireDuration) {
		return new WanderState();
	}

	return nullptr;
}

void kd::FygarFireState::Exit(GameObject*)
{
	m_Component->RemoveFlame();
}
#pragma endregion

#pragma region STATE_DIE
void kd::EnemyDieState::Enter(GameObject* object)
{
	object->GetComponent<SpriteComponent>()->SetCurrentClip(EnemyBehaviour::Animation::Crush);
	std::cout << "Enter Enemy-DieState" << std::endl;
}

kd::BaseState * kd::EnemyDieState::Update(GameObject * object)
{
	if (m_DyingElapsedSec > m_DyingDuration)
	{
		SceneManager::GetInstance().GetActiveScene()->RemoveGameObject(object);
		return nullptr;
	}

	m_DyingElapsedSec += Time::GetInstance().DeltaTime();

	return nullptr;
}

void kd::EnemyDieState::Exit(GameObject*){}
#pragma endregion





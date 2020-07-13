#include "pch.h"
#include "EnemyBehaviour.h"
#include "DigDugGame.h"
#include "DigDugPrefabs.h"
#include "RockBehaviour.h"
#include "EnemyState.h"
#include "StateMachine.h"
#include "ColliderComponent.h" 

kd::EnemyBehaviour::EnemyBehaviour(GameObject* player, SpriteInfo&& dyingSprite)
	: m_StateMachine(new StateMachine(new WanderState()))
	, m_Player(player)
	, m_DyingSpriteInfo(dyingSprite)
	, m_Sprite(nullptr)
	, m_GetRocked(false)
	, m_GetPumped(false)
	, m_AttackState(AttackState::None)
{
	m_DyingSpriteInfo.Clips.insert({EnemyBehaviour::Animation::Bloat, SpriteClip(0, 2)});
	m_DyingSpriteInfo.Clips.insert({EnemyBehaviour::Animation::Explode, SpriteClip(2, 1)});
}

kd::EnemyBehaviour::~EnemyBehaviour()
{
	SafeDelete(m_StateMachine);
}

void kd::EnemyBehaviour::Initialize()
{
	// Enter DefaultState
	m_StateMachine->Initialize(GetGameObject());

	m_Sprite = GetGameObject()->GetComponent<SpriteComponent>();
	m_SpriteInfo = m_Sprite->GetSpriteInfo();

	// Set Collision Callback with Lamda
	ColliderComponent::CollisionCallback callback = [&](CollisionHit* hit) { this->TriggerEnter(hit); };
	GetGameObject()->GetComponent<ColliderComponent>()->SetCollisionCallback(callback);
}

void kd::EnemyBehaviour::Update()
{
	m_StateMachine->Update(GetGameObject());
}

void kd::EnemyBehaviour::Render() const{}

void kd::EnemyBehaviour::TriggerEnter(CollisionHit* hit)
{
	m_GetPumped = (hit->gameObject->GetTag() == GameObjectTag::PumpArrow);
	
	if(hit->gameObject->GetTag() == GameObjectTag::Rock && m_GetRocked == false)
	{
		const auto rockBehaviour = hit->gameObject->GetComponent<RockBehaviour>();
		if(rockBehaviour) {
			if(rockBehaviour->IsFalling()) {
				m_GetRocked = true;
				rockBehaviour->UpdateScore(m_Player);
			}
		}
			
	}
}

void kd::EnemyBehaviour::HandleAttack()
{
}



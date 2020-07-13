#include "pch.h"
#include "TaizoBehaviour.h"
#include "SpriteComponent.h"
#include "DigDugGame.h"
#include "BaseState.h"
#include "TaizoState.h"
#include "RockBehaviour.h"
#include "StateMachine.h"
#include "DigDugPrefabs.h"
#include "ColliderComponent.h"

kd::TaizoBehaviour::TaizoBehaviour(GameObject* pumpObject, float speed)
	: m_StateMachine(new StateMachine(new IdleState()))
	, m_PumpWeapon(pumpObject)
	, m_Speed(speed)
{
}

kd::TaizoBehaviour::~TaizoBehaviour()
{
	if(m_PumpWeapon->GetParent() == nullptr)
		SafeDelete(m_PumpWeapon);

	SafeDelete(m_StateMachine);
}

void kd::TaizoBehaviour::Initialize()
{
	m_StateMachine->Initialize(GetGameObject());
	// Set Callback with Lamda
	const ColliderComponent::CollisionCallback callback = [&](CollisionHit* hit) { this->TriggerEnter(hit); };
	GetGameObject()->GetComponent<ColliderComponent>()->SetCollisionCallback(callback);
}

void kd::TaizoBehaviour::Update()
{
	m_StateMachine->Update(GetGameObject());

	SetMove(false); // Reset Player Movement State
	SetPump(false);
}

void kd::TaizoBehaviour::Render() const
{
}

void kd::TaizoBehaviour::TriggerEnter(CollisionHit* hit)
{
	if(hit->gameObject->GetTag() == GameObjectTag::Fire || IsEnemy(hit->gameObject))
	{
		m_IsDead = true;
	}

	if(hit->gameObject->GetTag() == GameObjectTag::Rock)
	{
		const auto rockBehaviour = hit->gameObject->GetComponent<RockBehaviour>();
		if(rockBehaviour)
		{
			if(rockBehaviour->IsFalling())
			{
				m_IsDead = true;
			}
		}
	}
}

bool kd::TaizoBehaviour::IsEnemy(GameObject * object)
{
	auto tag = object->GetTag();
	return (tag == GameObjectTag::Pooka || tag == GameObjectTag::Fygar);
}

void kd::TaizoBehaviour::Reset()
{
	SetDead(false);
	auto& transform = GetGameObject()->GetTransform();
	transform.SetFlip(Transform::Flip::None);
	transform.SetRotation(0);
	transform.SetPosition(0, DigDugGame::GetGameContext().GridSize, 0);
}


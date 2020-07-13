#include "pch.h"
#include "PumpBehaviour.h"
#include "TaizoBehaviour.h"
#include "FygarBehaviour.h"
#include "DigDugPrefabs.h"
#include "ColliderComponent.h"

void kd::PumpBehaviour::Initialize()
{
	ColliderComponent::CollisionCallback callback = [&](CollisionHit* hit) { this->TriggerEnter(hit); };
	GetGameObject()->GetComponent<ColliderComponent>()->SetCollisionCallback(callback);
	
	auto parent = GetGameObject()->GetParent();
	if(parent) 
		m_PlayerComponent = parent->GetComponent<TaizoBehaviour>();
}

void kd::PumpBehaviour::Update() {}

void kd::PumpBehaviour::Render() const {}

void kd::PumpBehaviour::TriggerEnter(CollisionHit* hit)
{
	if(m_PlayerComponent && m_PlayerComponent->IsEnemy(hit->gameObject))
	{
		auto type = hit->gameObject->GetTag() == GameObjectTag::Fygar ? EnemyBehaviour::Type::Fygar : EnemyBehaviour::Type::Pooka;
		if (m_PlayerComponent)  
			m_PlayerComponent->SetEnemy(type);
	}
}

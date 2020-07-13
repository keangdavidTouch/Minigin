#include "pch.h"
#include "RockBehaviour.h"
#include "RockState.h"
#include "DigTileComponent.h"
#include "DigDugGame.h"
#include "DigDugPrefabs.h"
#include "StateMachine.h"
#include "TaizoBehaviour.h"
#include "ColliderComponent.h" 

kd::RockBehaviour::RockBehaviour() 
	: m_StateMachine(new StateMachine(new RockIdleState()))
{
}

kd::RockBehaviour::~RockBehaviour()
{
	SafeDelete(m_StateMachine);
}

void kd::RockBehaviour::Initialize()
{
	m_StateMachine->Initialize(GetGameObject());

	// Set Callback with Lamda
	const ColliderComponent::CollisionCallback callback = [&](CollisionHit* hit) { this->TriggerEnter(hit); };
	GetGameObject()->GetComponent<ColliderComponent>()->SetCollisionCallback(callback);
}

void kd::RockBehaviour::Update()
{
	m_StateMachine->Update(GetGameObject());
}

void kd::RockBehaviour::Render() const {}

void kd::RockBehaviour::TriggerEnter(CollisionHit* hit)
{
	std::string tag = hit->gameObject->GetTag();

	if(tag == GameObjectTag::Dirt)
	{
		DigTileComponent* tileComponent = hit->gameObject->GetComponent<DigTileComponent>();

		if(tileComponent && tileComponent->IsEnable() == false) {

			if((m_TriggerObject && GetGameObject()->GetTransform().GetPosition().y >= m_TriggerObject->GetTransform().GetPosition().y) == false) {
				m_ShouldFall = true;

				if(m_OccupiedTile != nullptr) {
					m_OccupiedTile->SetDiggable(true);
				}
			}
		}
		else {
			m_ShouldFall = false;

			if(m_OccupiedTile == nullptr) {
				m_OccupiedTile = tileComponent;
				m_OccupiedTile->SetDiggable(false);
			}
		}

		if(GetGameObject()->GetTransform().GetPosition().y >= DigDugGame::GetGameContext().Boundary.MaxY)
			m_ShouldFall = false;
	}
}

void kd::RockBehaviour::UpdateScore(GameObject* player)
{
	if(player)
		player->GetSubject().Notify(int(TaizoBehaviour::EventType::RockEnemy), player);
}

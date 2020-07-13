#include "pch.h"
#include "DigTileComponent.h"
#include "TileRenderComponent.h"
#include "PathFinder.h"
#include "SpriteComponent.h"
#include "SpriteSheetManager.h"
#include "DigDugGame.h"
#include "TaizoBehaviour.h"
#include "DigDugPrefabs.h"
#include "ColliderComponent.h"

SDL_Rect kd::DigTileComponent::BlackTileSrcRect = SpriteSheetManager::GetInstance().GetSourceRect(SpriteInfo(1, SDL_Rect{0, 0, 8, 8}, 2, 1));

kd::DigTileComponent::DigTileComponent()
	: m_TileComponent(nullptr)
{
}

void kd::DigTileComponent::Initialize()
{
	m_TileComponent = GetGameObject()->GetComponent<TileRenderComponent>();

	// Set Callback with Lamda
	const ColliderComponent::CollisionCallback callback = [&](CollisionHit* hit) { this->TriggerEnter(hit); };
	GetGameObject()->GetComponent<ColliderComponent>()->SetCollisionCallback(callback);

	const auto pos = GetGameObject()->GetTransform().GetPosition();
	if (!PathFinder::GetInstance().IsCellAtPosBlock(int(pos.y), int(pos.x))) 
	{
		m_TileComponent->ChangeSourceRect(BlackTileSrcRect);
	}
}

void kd::DigTileComponent::Update(){}

void kd::DigTileComponent::Render() const {}

void kd::DigTileComponent::TriggerEnter(CollisionHit* hit)
{	
	if (hit->gameObject->GetTag() == GameObjectTag::Player)
	{
		if(m_Diggable == false) {
		
			auto& playerTransform = hit->gameObject->GetTransform();
			auto playerPos = playerTransform.GetPosition();
			const auto tilePos = GetGameObject()->GetTransform().GetPosition();
			const auto gridSize = DigDugGame::GetGameContext().GridSize;

			if(hit->direction.y == 1) {
				playerPos.y = tilePos.y - gridSize;
			}
			else if(hit->direction.y == -1) {
				playerPos.y = tilePos.y + gridSize;
			}

			if(hit->direction.x == 1) {
				playerPos.x = tilePos.x + gridSize;
			}
			else if(hit->direction.x == -1) {
				playerPos.x = tilePos.x - gridSize;
			}

			playerTransform.SetPosition(playerPos);
			return;
		}

		m_Enable = false;
		const auto pos = GetGameObject()->GetTransform().GetPosition();
		if(PathFinder::GetInstance().SetCellAtPoAsBlock(int(pos.y), int(pos.x),false))
		{
			m_TileComponent->ChangeSourceRect(BlackTileSrcRect);
		}
	}
}

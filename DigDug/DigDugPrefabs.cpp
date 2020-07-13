#include "pch.h"
#include <SDL.h>
#include "GameObject.h"
#include "DigDugGame.h"
#include "DigDugPrefabs.h"
#include "InputManager.h"
#include "SpriteSheetManager.h"
//Observers
#include "HealthDisplay.h"
#include "ScoreDisplay.h"
//Components
#include "TaizoBehaviour.h"
#include "PoogaBehaviour.h"
#include "FygarBehaviour.h"
#include "RenderComponent.h"
#include "ColliderComponent.h"
#include "AIComponent.h"
#include "PumpBehaviour.h"
#include "RockBehaviour.h"
#include "TextComponent.h"
#include "DigTileComponent.h"
#include "TileRenderComponent.h"

kd::GameObject * kd::TaizoPrefab::Create(GameObject* lifeText, GameObject* scoreText)
{
	auto spriteSize = PrefabContext::spriteSize;
	auto spriteTexture = SpriteSheetManager::GetInstance().GetTexture(0);
	auto pumpRect = SpriteSheetManager::GetInstance().GetSourceRect(SpriteInfo(1, SDL_Rect{0, 18, spriteSize, spriteSize}, 0, 13));
	auto pumpRect2 = SpriteSheetManager::GetInstance().GetSourceRect(SpriteInfo(1, SDL_Rect{0, 18, spriteSize, spriteSize}, 0, 13));
	auto arrowRect = SpriteSheetManager::GetInstance().GetSourceRect(SpriteInfo(1, SDL_Rect{0, 18, spriteSize, spriteSize}, 0, 12));

	auto pump1 = new GameObject();
	pump1->GetTransform().SetLocalPosition(-float(PrefabContext::spriteSize) * 2, 0);
	pump1->AddComponent(new RenderComponent(spriteTexture, pumpRect));
	auto pump2 = new GameObject();
	pump2->GetTransform().SetLocalPosition(-float(PrefabContext::spriteSize), 0);
	pump2->AddComponent(new RenderComponent(spriteTexture, pumpRect2));

	auto pumpArrowBase = new GameObject(GameObjectTag::PumpArrow);
	pumpArrowBase->GetTransform().SetLocalPosition(0, 0);
	pumpArrowBase->AddComponent(new PumpBehaviour());
	pumpArrowBase->AddComponent(new RenderComponent(spriteTexture, arrowRect));
	pumpArrowBase->AddComponent(new ColliderComponent(PrefabContext::gridSizeInt, PrefabContext::gridSizeInt));
	pumpArrowBase->AddChild(pump1);
	pumpArrowBase->AddChild(pump2);

	auto taizoSprite = SpriteInfo(1, SDL_Rect{0, 0, spriteSize, spriteSize}, 0, 0, 0.1f); 
	taizoSprite.Clips.insert({TaizoBehaviour::Animation::Idle, SpriteClip(6, 1)});
	taizoSprite.Clips.insert({TaizoBehaviour::Animation::Run, SpriteClip(6, 2)});
	taizoSprite.Clips.insert({TaizoBehaviour::Animation::Dig, SpriteClip(2, 2)});
	taizoSprite.Clips.insert({TaizoBehaviour::Animation::Shoot, SpriteClip(9, 1)});
	taizoSprite.Clips.insert({TaizoBehaviour::Animation::Pump, SpriteClip(12, 2)});
	taizoSprite.Clips.insert({TaizoBehaviour::Animation::Die, SpriteClip(0, 5)});

	auto taizo = new GameObject(GameObjectTag::Player);
	taizo->GetSubject().AddObserver(new HealthDisplay(lifeText));
	taizo->GetSubject().AddObserver(new ScoreDisplay(scoreText));
	taizo->GetTransform().SetScale(PrefabContext::scale);
	taizo->GetTransform().SetPosition(PrefabContext::gridSize * 6, PrefabContext::gridSize * 8); // position in the middle of screen
	taizo->AddComponent(new TaizoBehaviour(pumpArrowBase, 2.f));
	taizo->AddComponent(new RenderComponent());
	taizo->AddComponent(new ColliderComponent(PrefabContext::npcRect));
	taizo->AddComponent(new SpriteComponent(taizoSprite, TaizoBehaviour::Animation::Idle));

	return taizo;
}

kd::GameObject * kd::PookaPrefab::Create(GameObject* taizo)
{
	auto pookaSprite = SpriteInfo(1, SDL_Rect{0, 41, PrefabContext::spriteSize, PrefabContext::spriteSize}, 0, 0, 0.2f);
	pookaSprite.Clips.insert({EnemyBehaviour::Animation::Bounce, SpriteClip(0, 2)});
	pookaSprite.Clips.insert({EnemyBehaviour::Animation::Crush, SpriteClip(4, 1)});
	pookaSprite.Clips.insert({EnemyBehaviour::Animation::Ghost, SpriteClip(2, 2)});

	auto pooka = new GameObject(GameObjectTag::Pooka);
	pooka->GetTransform().SetPosition( PrefabContext::gridSize * 10, PrefabContext::gridSize * 4);
	pooka->GetTransform().SetScale(PrefabContext::scale);
	pooka->AddComponent(new RenderComponent());
	pooka->AddComponent(new SpriteComponent(pookaSprite, EnemyBehaviour::Animation::Bounce));
	pooka->AddComponent(new ColliderComponent(PrefabContext::npcRect));
	pooka->AddComponent(new PookaBehaviour(taizo));
	pooka->AddComponent(new AIComponent(taizo, PrefabContext::gridSize, false));

	return pooka;
}

kd::GameObject * kd::FygarPrefab::Create(GameObject* taizo)
{
	auto spriteSize = PrefabContext::spriteSize;
	auto spriteTexture = SpriteSheetManager::GetInstance().GetTexture(0);
	auto flameRect1 = SpriteSheetManager::GetInstance().GetSourceRect(SpriteInfo(0, SDL_Rect{236, 66, spriteSize, spriteSize}, 0));
	auto flameRect2 = SpriteSheetManager::GetInstance().GetSourceRect(SpriteInfo(0, SDL_Rect{236 + spriteSize, 66, spriteSize, spriteSize}, 0, 0));

	auto flame2 = new GameObject(GameObjectTag::Fire);
	flame2->GetTransform().SetLocalPosition(float(spriteSize), 0);
	flame2->AddComponent(new RenderComponent(spriteTexture, flameRect2));
	
	auto flame1 = new GameObject(GameObjectTag::Fire);
	flame1->GetTransform().SetLocalPosition(float(spriteSize), 0);
	flame1->AddComponent(new RenderComponent(spriteTexture, flameRect1));
	flame1->AddComponent(new ColliderComponent(PrefabContext::gridSizeInt * 2, PrefabContext::gridSizeInt));
	flame1->AddChild(flame2);

	auto fygarSprite = SpriteInfo(1, SDL_Rect{0, 67, spriteSize, spriteSize}, 0, 0, 0.2f);
	fygarSprite.Clips.insert({EnemyBehaviour::Animation::Bounce, SpriteClip(0, 2)});
	fygarSprite.Clips.insert({EnemyBehaviour::Animation::Crush, SpriteClip(5, 1)});
	fygarSprite.Clips.insert({EnemyBehaviour::Animation::Ghost, SpriteClip(3, 2)});

	auto fygar = new GameObject(GameObjectTag::Fygar);
	fygar->GetTransform().SetPosition(0, PrefabContext::gridSize * 5);
	fygar->GetTransform().SetScale(PrefabContext::scale);
	fygar->AddComponent(new RenderComponent());
	fygar->AddComponent(new SpriteComponent(fygarSprite, EnemyBehaviour::Animation::Bounce));
	fygar->AddComponent(new ColliderComponent(PrefabContext::npcRect));
	fygar->AddComponent(new FygarBehaviour(flame1, taizo));
	fygar->AddComponent(new AIComponent(taizo, PrefabContext::gridSize, false));

	return fygar;
}

kd::GameObject * kd::RockPrefab::Create()
{
	auto rockSprite = SpriteInfo(1, SDL_Rect{0, 91, PrefabContext::spriteSize, PrefabContext::spriteSize}, 0, 0, 0.2f);
	rockSprite.Clips.insert({RockBehaviour::Animation::Idle, SpriteClip(0, 1)});
	rockSprite.Clips.insert({RockBehaviour::Animation::Shake, SpriteClip(0, 2)});
	rockSprite.Clips.insert({RockBehaviour::Animation::Crack, SpriteClip(2, 2)});

	auto rockObject = new GameObject(GameObjectTag::Rock);
	rockObject->GetTransform().SetPosition( PrefabContext::gridSize * 3, PrefabContext::gridSize * 12);
	rockObject->GetTransform().SetScale(PrefabContext::scale, PrefabContext::scale);
	rockObject->AddComponent(new RockBehaviour());
	rockObject->AddComponent(new RenderComponent());
	rockObject->AddComponent(new SpriteComponent(rockSprite, RockBehaviour::Animation::Idle));
	rockObject->AddComponent(new ColliderComponent(PrefabContext::rockRect));

	return rockObject;
}

kd::GameObject * kd::TextPrefab::Create(std::string text, int size, float column, float row)
{
	GameObject* textObject = new GameObject();
	textObject->GetTransform().SetPosition(PrefabContext::gridSize * column, PrefabContext::gridSize * row);
	textObject->AddComponent(new RenderComponent());
	textObject->AddComponent(new TextComponent(text, PrefabContext::fontName, size));
	return textObject;
}

kd::GameObject * kd::GroundTilePrefab::Create(const SpriteInfo& sprite, int column, int row)
{
	auto dirtTile = new GameObject(GameObjectTag::Dirt);
	dirtTile->GetTransform().SetPosition(PrefabContext::gridSize * column, PrefabContext::gridSize * row, 0);
	dirtTile->GetTransform().SetScale(PrefabContext::scale);
	dirtTile->AddComponent(new TileRenderComponent(sprite, 2, 2));
	dirtTile->AddComponent(new ColliderComponent(PrefabContext::gridSizeInt, PrefabContext::gridSizeInt));
	dirtTile->AddComponent(new DigTileComponent());
	 
	return dirtTile;
}

void kd::GroundTilePrefab::CreateTiles(int nrOfCol, int nrOfRow, std::function<void(int, int)> func)
{
	for (int i = 0; i < nrOfRow; i++) {
		for(int j = 0; j < nrOfCol; j++) {
			func(i, j);
		}
	}
}

kd::GameObject * kd::LevelTilePrefab::Create(const SpriteInfo & sprite, int cols, int rows, float x, float y)
{
	auto tile = new GameObject();
	tile->GetTransform().SetPosition(x, y, 0);
	tile->GetTransform().SetScale(PrefabContext::scale);
	tile->AddComponent(new TileRenderComponent(sprite, cols, rows));
	return tile;
}

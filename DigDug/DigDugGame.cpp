#pragma region INCLUDES...
#include "pch.h"
#include <vld.h>
#include <SDL.h>
#include <thread>
#include "DigDugGame.h"
#include "Scene.h"
#include "GameObject.h"
//Manangers
#include "InputManager.h"
#include "SceneManager.h"
#include "SpriteSheetManager.h"
//Commands
#include "PumpCommand.h"
#include "MoveCommand.h"
#include "FygarFlameCommand.h"
#include "SwitchSceneCommand.h"
#include "MoveWithJoystickCommand.h"
//Helpers
#include "FpsComponent.h"
#include "DigDugPrefabs.h"
#include "LevelLoader.h"
#include "PathFinder.h"
#pragma endregion

//Static Variable
kd::GameContext kd::DigDugGame::m_GameContext{};

kd::DigDugGame::DigDugGame(GameSetting& setting) : MiniginGame(setting)
{
	m_GameContext = GameContext(setting.WindowWidth, setting.WindowHeight);
}

void kd::DigDugGame::LoadGame()
{
	LoadDigDugSingleMode();
}

void kd::DigDugGame::LoadDigDugSingleMode()
{
	auto scene = SceneManager::GetInstance().CreateScene("DigDug");
	LoadResources();
	LoadLevel(); 
	AddLevelTiles(scene);
	
	scene->Add(TextPrefab::Create("ROUND", 15, 12, 15));
    scene->Add(TextPrefab::Create("1", 15, 13, 15.5f));
    scene->Add(TextPrefab::Create("Player SCORE", 20,4.5f, 0));
    const auto scoreText = scene->Add(TextPrefab::Create("0", 20, 6, 0.5f));
	const auto lifeText	= scene->Add(TextPrefab::Create("LIFE 3", 18, 0, 15.5f));

	const auto taizo = scene->Add(TaizoPrefab::Create(lifeText, scoreText));
	scene->Add(FygarPrefab::Create(taizo));
	scene->Add(PookaPrefab::Create(taizo));
	scene->Add(RockPrefab::Create());
	
	auto& inputManager = InputManager::GetInstance();
	inputManager.RegisterAction(0, std::make_shared<MoveCommand>(taizo, TaizoBehaviour::MoveDirection::Left), 'A', CtrlButton::ButtonLeft, CIndex::One, TriggerState::Down);
	inputManager.RegisterAction(1, std::make_shared<MoveCommand>(taizo, TaizoBehaviour::MoveDirection::Right), 'D', CtrlButton::ButtonRight, CIndex::One, TriggerState::Down);
	inputManager.RegisterAction(2, std::make_shared<MoveCommand>(taizo, TaizoBehaviour::MoveDirection::Up), 'W', CtrlButton::ButtonUp, CIndex::One, TriggerState::Down);
	inputManager.RegisterAction(3, std::make_shared<MoveCommand>(taizo, TaizoBehaviour::MoveDirection::Down), 'S', CtrlButton::ButtonDown, CIndex::One, TriggerState::Down);
	inputManager.RegisterAction(6, std::make_shared<PumpCommand>(taizo), 'P', CtrlButton::None, CIndex::One, TriggerState::Pressed);

	AddDebugObject(scene);
}

void kd::DigDugGame::LoadResources()
{
	SpriteSheetManager::GetInstance().Load("DigDug_SpriteSheet.png", 0);
	SpriteSheetManager::GetInstance().Load("Ground_SpriteSheet.png", 1);
}

void kd::DigDugGame::LoadLevel()
{
	PathFinder::GetInstance().Init(14, 16, int(DigDugGame::GetGameContext().GridSize));
	LevelLoader loader = LevelLoader();
	loader.ReadBinary("../Resources/lvl1.bin");
}

void kd::DigDugGame::AddLevelTiles(Scene* scene)
{
	int spriteSheetID = 1;
	int nrOfCols = GetGameContext().Col * 2;
	int tileSize = static_cast<int>(GetGameContext().SpriteSize/2);

	auto blueTile = SpriteInfo(1, {0, 0, tileSize, tileSize}, spriteSheetID, 2);
	scene->Add(LevelTilePrefab::Create(blueTile, nrOfCols, 4));
	scene->Add(LevelTilePrefab::Create(blueTile, nrOfCols, 2, 0, GetGameContext().GridSize * 15));

	auto groundTile1 = SpriteInfo(1, {0, 0, tileSize, tileSize}, spriteSheetID, 4);
	auto groundTile2 = SpriteInfo(1, {0, 9, tileSize, tileSize}, spriteSheetID, 7);
	auto groundTile3 = SpriteInfo(1, {0, 18, tileSize, tileSize}, spriteSheetID, 7);
	auto groundTile4 = SpriteInfo(1, {0, 27, tileSize, tileSize}, spriteSheetID, 7);

	GroundTilePrefab::CreateTiles(3, nrOfCols, [&](int col, int row){ scene->Add(GroundTilePrefab::Create(groundTile1, col, row+2)); });
	GroundTilePrefab::CreateTiles(3, nrOfCols, [&](int col, int row){ scene->Add(GroundTilePrefab::Create(groundTile2, col, row+5)); });
	GroundTilePrefab::CreateTiles(3, nrOfCols, [&](int col, int row){ scene->Add(GroundTilePrefab::Create(groundTile3, col, row+8)); });
	GroundTilePrefab::CreateTiles(4, nrOfCols, [&](int col, int row){ scene->Add(GroundTilePrefab::Create(groundTile4, col, row+11)); });
}

#pragma region DEBUG
void kd::DigDugGame::AddDebugObject(Scene* scene)
{
	auto fpsObject = TextPrefab::Create("0 FPS", 15, 0, 0);
	fpsObject->AddComponent(new FpsComponent());
	scene->Add(fpsObject);
}
#pragma endregion



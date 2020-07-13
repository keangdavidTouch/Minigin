#pragma once
#include "DigDugGame.h"
#include "SpriteComponent.h"

namespace kd
{
	namespace PrefabContext {
		const float scale = DigDugGame::GetGameContext().Scale;
		const float gridSize = DigDugGame::GetGameContext().GridSize;
		const int gridSizeInt = static_cast<int>(gridSize);
		const int spriteSize = DigDugGame::GetGameContext().SpriteSize;
		const std::string fontName = "digdug_font.ttf";
		const SDL_Rect npcRect{ 3, 3, gridSizeInt - 6, gridSizeInt - 6 }; 
		const SDL_Rect rockRect{ 6, 20, gridSizeInt - 12, gridSizeInt - 12 };
	};

	namespace GameObjectTag {
		const std::string Player = "Player";
		const std::string Pooka = "Pooka";
		const std::string Fygar = "Fygar";
		const std::string Rock = "Rock";
		const std::string Fire = "Fire";
		const std::string Dirt = "Dirt";
		const std::string PumpArrow = "PumpArrow";
	}

	class GameObject;

	class TaizoPrefab {
	
	public:
		static GameObject* Create(GameObject* lifeText, GameObject* scoreText);
	};

	class FygarPrefab {
	
	public:
		static GameObject* Create(GameObject* taizo);
	};

	class PookaPrefab {
	
	public:
		static GameObject* Create(GameObject* taizo);
	};

	class RockPrefab {
	
	public:
		static GameObject* Create();
	};
	
	class TextPrefab {
	public:
		static GameObject* Create(std::string text, int size, float column, float row);
	};

	class GroundTilePrefab {
	public:
		static GameObject* Create(const SpriteInfo& sprite, int column, int row);
		static void CreateTiles(int nrOfCol, int nrOfRow, std::function<void(int, int)> func);
	};

	class LevelTilePrefab {
	public:
		static GameObject* Create(const SpriteInfo & sprite, int cols, int rows, float x = 0.f, float y = 0.f);
	};
}
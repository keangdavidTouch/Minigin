#pragma once
#include "MiniginGame.h"
#include "GameStruct.h"
#include <functional>

namespace kd
{
	class Scene;

	class DigDugGame final : public MiniginGame
	{
	public:
		DigDugGame(GameSetting& setting);
		~DigDugGame() = default;
		
		void LoadGame() override;
		static const GameContext& GetGameContext() { return m_GameContext; };
	private:
		static GameContext m_GameContext;
		void LoadDigDugSingleMode();
		void LoadResources();
		void LoadLevel();
		void AddLevelTiles(Scene* scene);
		void AddDebugObject(Scene* scene);
	};
}



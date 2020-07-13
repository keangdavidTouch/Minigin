#pragma once
#include <chrono>

struct SDL_Window;

namespace kd
{
	struct GameSetting
	{
		GameSetting(int width = 672, int height = 672, std::string name = "Minigin", std::string resource = "../Resources/") 
		: WindowWidth(width), WindowHeight(height), WindowName(std::move(name)), ResourcePath(std::move(resource)){};

		int WindowWidth, WindowHeight; 
		std::string WindowName;
		std::string ResourcePath;
	};

	class MiniginGame
	{
	public:
		// Rule of 5
		MiniginGame(const MiniginGame& other) = delete;
		MiniginGame(MiniginGame&& other) noexcept = delete;
		MiniginGame& operator=(const MiniginGame& other) = delete;
		MiniginGame& operator=(MiniginGame&& other) noexcept = delete;
		MiniginGame(GameSetting& setting);
		~MiniginGame() = default;

		void Run();
		/*static void SetGameSetting(GameSetting& setting) { m_Settings = setting; }
		static const GameSetting& GetGameSettings() { return m_Settings; }*/

	protected :
		virtual void LoadGame() = 0; /***** Code constructing the scene world starts here *****/
	private:
		void InitializeGame();
		void InitializeWindow();
		void Cleanup();
		void MainGameLoop();

		SDL_Window* window{};

		//static GameSetting m_Settings;
		GameSetting m_Settings;
		const int m_MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		float m_Lag = 0.0f;
		std::chrono::steady_clock::time_point m_LastUpdateTime{};
	};
}
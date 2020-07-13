#pragma once

struct SDL_Window;

namespace kd
{
	class GameObject;

	class MiniginGame
	{
	public:


		void Initialize();
		void LoadGame() ;
		void Cleanup();
		void Run();
	private:
		const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* window{};
		GameObject* fpsObject ;
	};
}
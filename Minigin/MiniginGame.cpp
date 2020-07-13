#include "MiniginPCH.h"
#include "MiniginGame.h"
#include <SDL.h>
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Time.h"
#include "ServiceLocator.h"

//kd::GameSetting kd::MiniginGame::m_Settings = kd::GameSetting();

kd::MiniginGame::MiniginGame(GameSetting& setting) : m_Settings(setting)
{
	
}

void kd::MiniginGame::InitializeGame()
{
	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init(m_Settings.ResourcePath.c_str());

	// Register Audio Service
	ServiceLocator::init();
	ServiceLocator::RegisterAudioService(new ConsoleAudio());
}

void kd::MiniginGame::InitializeWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		m_Settings.WindowName.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_Settings.WindowWidth,
		m_Settings.WindowHeight,
		SDL_WINDOW_OPENGL
	);

	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

void kd::MiniginGame::Run()
{
	InitializeWindow();
	InitializeGame();

	LoadGame();

	// Main loop flag
	bool quite = false;
	// Event Handler 
	SDL_Event event;

	m_LastUpdateTime = std::chrono::high_resolution_clock::now();

	while (!quite)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				quite = true;
		}

		MainGameLoop();
	}

	Cleanup();
}

void kd::MiniginGame::MainGameLoop()
{
	const auto currentUpdateTime = std::chrono::high_resolution_clock::now();
	const auto deltaTime = std::chrono::duration<float>(currentUpdateTime - m_LastUpdateTime).count();
	Time::GetInstance().m_DeltaTime = deltaTime;
	
	m_LastUpdateTime = currentUpdateTime;
	m_Lag += deltaTime;
	
	InputManager::GetInstance().ProcessInput();

	SceneManager::GetInstance().Update();

	while (m_Lag >= m_MsPerFrame) {

		SceneManager::GetInstance().FixedUpdate();
		m_Lag -= m_MsPerFrame;
	}

	Renderer::GetInstance().Render(); 
}

void kd::MiniginGame::Cleanup()
{
	ServiceLocator::Destroy();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

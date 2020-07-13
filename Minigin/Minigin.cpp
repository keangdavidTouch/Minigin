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
#include "Scene.h"
#include "Time.h"
#include "Component.h"
#include "SpriteSheetManager.h"
#include "SpriteComponent.h"

void kd::MiniginGame::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		672,
		768,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void kd::MiniginGame::LoadGame() 
{
	auto& scene = SceneManager::GetInstance().CreateScene("DigDug");

	/*auto texObject = new GameObject();
	texObject->AddComponent(new RenderComponent("background.jpg"));
	scene.Add(texObject);

	texObject = new GameObject();
	texObject->AddComponent(new RenderComponent("logo.png"));
	texObject->SetPosition(216, 180);
	scene.Add(texObject);

	auto fontObject = new GameObject();
	fontObject->AddComponent(new RenderComponent);
	fontObject->AddComponent(new TextComponent("Programming 4 Assignment", "Lingua.otf", 36));
	fontObject->SetPosition(80, 20);
	scene.Add(fontObject);*/

	/*auto fpsObject = new GameObject();*/

	//fpsObject->AddComponent(new RenderComponent());
	//fpsObject->AddComponent(new TextComponent("0 FPS", "Lingua.otf", 20));
	//fpsObject->AddComponent(new FpsComponent());
	fpsObject = new GameObject();
	fpsObject->GetTransform().SetScale(3, 3);
	fpsObject->AddComponent(new RenderComponent());
	fpsObject->AddComponent(new SpriteComponent(SpriteInfo(1, 0, 11, 16, 16, 0)));
	scene.Add(fpsObject);
}

void kd::MiniginGame::Cleanup()
{
	ServiceLocator::Destroy();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void kd::MiniginGame::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Resources/");

	LoadGame();
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& inputManager = InputManager::GetInstance();
		inputManager.RegisterAction(0, new InputAction(new FireCommand(), 'D', ControllerButton::ButtonA, ControllerIndex::One, TriggerState::Released));
		inputManager.RegisterAction(1, new InputAction(new DuckCommand(), 'A', ControllerButton::ButtonB, ControllerIndex::One, TriggerState::Pressed));
		inputManager.RegisterAction(2, new InputAction(new JumpCommand(), 'S', ControllerButton::ButtonY, ControllerIndex::One, TriggerState::Down));
		inputManager.RegisterAction(3, new InputAction(new FartCommand(), -1, ControllerButton::ButtonX, ControllerIndex::One, TriggerState::Pressed));

		// Register Audio Service
		ServiceLocator::init();
		ServiceLocator::RegisterAudioService(new ConsoleAudio());

		SpriteSheetManager::GetInstance().Load("DigDug_SpriteSheet.png", 0);

		bool doContinue = true;

		float lag = 0.0f;
		auto lastUpdateTime = std::chrono::high_resolution_clock::now();

		SDL_Event event;

		while (doContinue)
		{
			while(SDL_PollEvent(&event))
			{
				if(event.type == SDL_QUIT)
					doContinue = false;
			}

			const auto currentUpdateTime = std::chrono::high_resolution_clock::now();
			const auto deltaTime = std::chrono::duration<float>(currentUpdateTime - lastUpdateTime).count();
			Time::GetInstance().m_DeltaTime = deltaTime;
			
			lastUpdateTime = currentUpdateTime;
			lag += deltaTime;
			
			inputManager.ProcessInput();
			auto stickPos = inputManager.GetThumbstickPosition(int(ControllerIndex::One));

			sceneManager.Update();

			auto pos = fpsObject->GetTransform().GetPosition();
			fpsObject->SetPosition(pos.x += (stickPos.x * 3), pos.y += (stickPos.y * 3));

			while (lag >= msPerFrame) {

				sceneManager.FixedUpdate();
				lag -= msPerFrame;
			}

			renderer.Render(); //TODO: render(lag / MS_PER_UPDATE); 
		}
	}

	Cleanup();
}

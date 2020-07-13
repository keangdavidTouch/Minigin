#pragma once
#include "Singleton.h"
#include <unordered_map>

namespace kd
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		SceneManager();
		SceneManager(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) noexcept = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager& operator=(SceneManager&& other) noexcept = delete;
		~SceneManager() override;

		Scene* CreateScene(const std::string& name);
		void RemoveScene(const std::string& name);
		Scene* GetScene(const std::string& name);
		Scene* GetActiveScene();
		void SetActiveScene(const std::string& name);
		void GoNextScene();
		void GoPreviousScene();

		void Update();
		void FixedUpdate();
		void Render();

	private:
		std::unordered_map<std::string, Scene*> m_Scenes;
		Scene* m_ActiveScene = nullptr;
	};

}

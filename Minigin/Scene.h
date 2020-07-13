#pragma once
#include "SceneManager.h"

namespace kd
{
	class GameObject;
	class Scene
	{
		friend Scene* SceneManager::CreateScene(const std::string& name);
	public:
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		~Scene();

		GameObject* Add(GameObject* object);
		void RemoveGameObject(GameObject* object);
		void Update();
		void Render() const;

		std::string& GetSceneName();
		
	private: 
		explicit Scene(const std::string& name);

		std::string m_Name{};
		GameObject* m_ToDeleteObject = nullptr;
		std::vector<GameObject*> m_Objects{};

		void RemoveAttemptedDeleteGameObject(GameObject* object);
	};

}

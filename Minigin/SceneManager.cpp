#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

kd::SceneManager::SceneManager()
{
}

kd::SceneManager::~SceneManager()
{
	for(auto scene : m_Scenes)
	{
		SafeDelete(scene.second);
	}
}

void kd::SceneManager::Update()
{
	/*for(auto scene : m_Scenes)
	{
		scene.second->Update();
	}*/

	if (m_ActiveScene)
		m_ActiveScene->Update();
}

void kd::SceneManager::FixedUpdate()
{

}

void kd::SceneManager::Render()
{
	/*for (const auto scene : m_Scenes)
	{
		scene.second->Render();
	}*/
	
	if (m_ActiveScene)
		m_ActiveScene->Render();
}

kd::Scene* kd::SceneManager::CreateScene(const std::string& name)
{
	if (m_Scenes[name] == nullptr)
	{
		const auto scene = new Scene(name);
		m_Scenes[name] = scene;

		//Set Active Scene
		if (!m_ActiveScene)
			m_ActiveScene = scene;

		return scene;
	}

	std::cout << "LOG:: Scene with id " << name << " is already existed" << std::endl;
	return nullptr;
}

void kd::SceneManager::RemoveScene(const std::string& )
{
	//RemoveScene
}

kd::Scene* kd::SceneManager::GetScene(const std::string& name)
{
	return m_Scenes[name];
}

kd::Scene* kd::SceneManager::GetActiveScene()
{
	return m_ActiveScene;
}

void kd::SceneManager::SetActiveScene(const std::string& name)
{
	if (m_Scenes[name])
		m_ActiveScene = m_Scenes[name];
	else
		std::cout << "LOG:: Can't Activate Scene with name " << name << " is not existed" << std::endl;
}

void kd::SceneManager::GoNextScene()
{
	 for (auto it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
	 {
		 if ((it->second) == m_ActiveScene)
		 {
			 auto nextIt = std::next(it);
			 if (nextIt != m_Scenes.end())
				m_ActiveScene = nextIt->second;
			 else
				m_ActiveScene = m_Scenes.begin()->second;

			 break;
		 }
	 }
}

void kd::SceneManager::GoPreviousScene()
{
	 for (auto it = m_Scenes.begin(); it != m_Scenes.end(); ++it)
	 {
		 if ((it->second) == m_ActiveScene)
		 {
			 auto previousIt = std::prev(it);
			 if (previousIt != m_Scenes.end())
				 m_ActiveScene = previousIt->second;
			 else
				 m_ActiveScene = std::prev(m_Scenes.end())->second;

			 break;
		 }
	 }
}



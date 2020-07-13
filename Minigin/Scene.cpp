#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <algorithm>

kd::Scene::Scene(const std::string& name) 
	: m_Objects()
	, m_Name(name)
{
}



kd::Scene::~Scene()
{
	for (auto gameObject : m_Objects)
	{
		SafeDelete(gameObject);
	}
}

void kd::Scene::Update()
{
	//Remove/Delete Object in NextFrame
	if(m_ToDeleteObject)
	{
		RemoveAttemptedDeleteGameObject(m_ToDeleteObject);
		m_ToDeleteObject = nullptr;
	}

	for(auto gameObject : m_Objects)
	{
		gameObject->Update();
	}
}

void kd::Scene::Render() const
{
	for (const auto gameObject : m_Objects)
	{
		gameObject->Render();
	}
}

kd::GameObject* kd::Scene::Add(GameObject* object)
{
	m_Objects.push_back(object);
	object->Initalize();
	object->m_Scene = this;

	// Set Child to this parent scene as well
	for (auto child : object->m_Childs)
		child->m_Scene = this;

	return object;
}

void kd::Scene::RemoveGameObject(GameObject* object)
{
	object->OnRemoved();
	m_ToDeleteObject = object;
}

void kd::Scene::RemoveAttemptedDeleteGameObject(GameObject* object)
{
	auto it = std::find(m_Objects.begin(), m_Objects.end(), object);
	if (it != m_Objects.end())
	{
		m_Objects.erase(it);
		SafeDelete(object);
	}
	else
	{
		std::cout << "LOG:: Can't Perform Scene::RemoveGameObject() as object is not found" << std::endl;
	}	
}

std::string& kd::Scene::GetSceneName()
{
	return m_Name;
}


#pragma once
#include "Scene.h"
#include "Transform.h"
#include <functional>
#include "Subject.h"

namespace kd
{
	class BaseComponent;

	class GameObject final
	{

	friend GameObject* Scene::Add(GameObject* object);

	public:

	    GameObject(const std::string& tag = std::string());
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Initalize();
		void Update();
		void Render() const;
		void OnRemoved();

		//Transform
		Transform& GetTransform() { return m_Transform; };
		void UpdateTransform();

		//Tag
		const std::string& GetTag() const { return m_Tag; };
		void SetTag(const std::string& tag) { m_Tag = tag; }

		//Scene
		Scene& GetScene() const { return *m_Scene; }

		//Parent-Childs
		GameObject* GetParent() const { return m_Parent; };
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);

		//Components
		void AddComponent(kd::BaseComponent* pComponent);
		void RemoveComponent(kd::BaseComponent* pComponent);

		template<class T>
		T* GetComponent() {

			for (BaseComponent* component : m_Components) {
				T* castComponent = dynamic_cast<T*>(component);
				if(castComponent)
					return castComponent;
				}

			return nullptr;
		}

		//Observer
		Subject& GetSubject() { return m_Subject; };

	private:
		Subject m_Subject;
		std::string m_Tag;
		Transform m_Transform;
		Scene* m_Scene;
		GameObject* m_Parent;
		std::vector<GameObject*> m_Childs;
		std::vector<BaseComponent*> m_Components;
	};
}

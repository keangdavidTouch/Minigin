#pragma once
#include "GameObject.h"

namespace kd
{
	class BaseComponent
	{
	friend class kd::GameObject;
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() {};
		kd::GameObject* GetGameObject() const { return m_pGameObject; };
	protected:
		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() const = 0;
		virtual void OnGameObjectRemoved() {};
	private:
		kd::GameObject* m_pGameObject;
	};

}



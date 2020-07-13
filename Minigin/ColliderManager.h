#pragma once
#include "Singleton.h"

namespace kd {

	class ColliderComponent;

	class ColliderManager final : public Singleton<ColliderManager>
	{
	public:
		ColliderManager();
		~ColliderManager() = default;
		void AddComponent(ColliderComponent* collider);
		void RemoveComponent(ColliderComponent* collider);
		const std::vector<ColliderComponent*>& GetColliders() const;
	private:
		std::vector<ColliderComponent*> m_Colliders;
	};
}


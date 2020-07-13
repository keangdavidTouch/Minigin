#include "MiniginPCH.h"
#include "ColliderManager.h"
#include "ColliderComponent.h"

kd::ColliderManager::ColliderManager()
	: m_Colliders(std::vector<ColliderComponent*>())
{
}

void kd::ColliderManager::AddComponent(ColliderComponent* collider)
{
	if (collider == nullptr) return;

	auto it = std::find(m_Colliders.begin(), m_Colliders.end(), collider);
	if (it == m_Colliders.end())
	{
		m_Colliders.push_back(collider);
	}
}

void kd::ColliderManager::RemoveComponent(ColliderComponent* collider)
{
	if (collider == nullptr) return;

	auto it = std::find(m_Colliders.begin(), m_Colliders.end(), collider);
	if (it != m_Colliders.end())
	{
		m_Colliders.erase(it);
	}
}

const std::vector<kd::ColliderComponent*>& kd::ColliderManager::GetColliders() const
{
	return m_Colliders;
}

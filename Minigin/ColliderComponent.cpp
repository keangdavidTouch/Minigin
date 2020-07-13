#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "Renderer.h"
#include "ColliderManager.h"

kd::ColliderComponent::ColliderComponent(const SDL_Rect& rect) : m_Rect{0 ,0, rect.w, rect.h}, m_OffsetX(rect.x), m_OffsetY(rect.y), m_HitInfo(new CollisionHit())
{
}

kd::ColliderComponent::ColliderComponent(int w, int h, int offsetX, int OffsetY) : m_Rect{0 ,0, w, h}, m_OffsetX(offsetX), m_OffsetY(OffsetY), m_HitInfo(new CollisionHit())
{
}

kd::ColliderComponent::~ColliderComponent()
{
	ColliderManager::GetInstance().RemoveComponent(this);
	SafeDelete(m_HitInfo);
}

void kd::ColliderComponent::Initialize()
{
	ColliderManager::GetInstance().AddComponent(this);
}

void kd::ColliderComponent::OnGameObjectRemoved()
{
	ColliderManager::GetInstance().RemoveComponent(this);
}

void kd::ColliderComponent::Update()
{
	const auto pos = GetGameObject()->GetTransform().GetPosition();
	m_Rect.x = m_OffsetX + static_cast<int>(pos.x);
	m_Rect.y = m_OffsetY + static_cast<int>(pos.y);

	const auto& others = ColliderManager::GetInstance().GetColliders();
	for(auto other : others)
	{
		if (other == this) continue;

		if (Collide(other))
		{
			auto direction = glm::vec2(0,0);
			auto otherRect = other->m_Rect;
			auto r1 = glm::vec2(m_Rect.x + m_Rect.w/2, m_Rect.y + m_Rect.h/2);
			auto r2 = glm::vec2(otherRect.x + otherRect.w/2, otherRect.y + otherRect.h/2);

			if(r1.x > r2.x)
				direction.x = -1;
			else if(r1.x < r2.x)
				direction.x = 1;

			if(r1.y < r2.y)
				direction.y = -1;
			else if(r1.y > r2.y)
				direction.y = 1;

			m_HitInfo->direction = direction;
			m_HitInfo->gameObject = other->GetGameObject();

			OnTrigger(m_HitInfo);
		}
	}
}

void kd::ColliderComponent::Render() const
{
	//#DEBUG
	//SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(),255, 255, 255, 0);
	//SDL_RenderDrawRect(Renderer::GetInstance().GetSDLRenderer(), &m_Rect);
}


bool kd::ColliderComponent::Collide(ColliderComponent* other)
{
	if(m_Enabled == false)
		return false; 

	// If one rectangle is on left side of the other
	if ( (m_Rect.x + m_Rect.w) < other->m_Rect.x || (other->m_Rect.x +  other->m_Rect.w) < m_Rect.x )
	{
		return false;
	}

	// If one rectangle is under the other
	if (m_Rect.y > (other->m_Rect.y + other->m_Rect.h) ||  other->m_Rect.y > (m_Rect.y + m_Rect.h) )
	{
		return false;
	}

	return true;
}

void kd::ColliderComponent::SetCollisionCallback(CollisionCallback callback)
{
	m_CollisionCallback = callback;
}

void kd::ColliderComponent::OnTrigger(CollisionHit* hit)
{
	if(m_CollisionCallback)
	{
		m_CollisionCallback(hit);
	}
}


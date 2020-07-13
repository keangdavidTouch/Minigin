#pragma once
#include "BaseComponent.h"
#include <SDL.h>

namespace kd
{
	class GameObject;

	struct CollisionHit {
		GameObject* gameObject;
		glm::vec2 direction;
	};

	class ColliderComponent final : public BaseComponent
	{
	public:

		typedef std::function<void(CollisionHit* hit)> CollisionCallback;

		ColliderComponent(const SDL_Rect& rect);
		ColliderComponent(int w, int h, int offsetX = 0, int OffsetY = 0);
		~ColliderComponent();

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void OnGameObjectRemoved() override;

		void SetEnable(bool enable) { m_Enabled = enable; }
		const bool IsEnable() { return m_Enabled; }; 

		void SetCollisionCallback(CollisionCallback callback);
		void OnTrigger(CollisionHit* hit);
	private:
		bool m_Enabled = true;
		int m_OffsetX, m_OffsetY;
		SDL_Rect m_Rect;
		CollisionHit* m_HitInfo;
		bool Collide(ColliderComponent* other);
		CollisionCallback m_CollisionCallback;
	};
}



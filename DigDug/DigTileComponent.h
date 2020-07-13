#pragma once
#include "BaseComponent.h"
#include <SDL.h>

namespace kd
{
	class TileRenderComponent;
	struct CollisionHit;

	class DigTileComponent final : public BaseComponent
	{
	public:
		DigTileComponent();
		~DigTileComponent() = default;

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void TriggerEnter(CollisionHit* hit);
		const bool IsEnable() { return m_Enable; } 
		void SetDiggable(bool enable) { m_Diggable = enable; }
	private:
		bool m_Enable = true;
		bool m_Diggable = true;
		static SDL_Rect BlackTileSrcRect;
		TileRenderComponent* m_TileComponent;
	};
}



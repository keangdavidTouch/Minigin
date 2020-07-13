#pragma once
#include "BaseComponent.h"
#include <SDL.h>

namespace kd
{
	struct SpriteInfo;
	class SpriteComponent;

	class TileRenderComponent final : public BaseComponent 
	{
	public:
		TileRenderComponent(const SpriteInfo& info, int cols, int rows); 
		~TileRenderComponent();

		void Initialize() override;
		void Update() override;
		void Render() const override;
	private:
		std::vector<SDL_Rect*> m_DescRects;
		int m_Rows, m_Cols;
		SDL_Rect* m_SpriteSourceRect;
		std::shared_ptr<Texture2D> m_Texture;
	};
}


#pragma once
#include "BaseComponent.h"
#include <SDL.h>
#include "Texture2D.h"

namespace kd
{
	struct SpriteInfo;
	class SpriteComponent;

	class TileRenderComponent final : public BaseComponent 
	{
	public:
		TileRenderComponent(const SpriteInfo& info, int cols, int rows); 
		~TileRenderComponent() = default;

		void Initialize() override;
		void Update() override;
		void Render() const override;
		void ChangeSourceRect(SDL_Rect& rect) { m_SpriteSourceRect = rect; };
		void SetTexture(std::shared_ptr<Texture2D> texture) { m_Texture = texture; };
		void SetRow(int row) { m_Rows = row; };
		void SetCol(int col) { m_Cols = col; };
	private:
		std::vector<SDL_Rect> m_DescRects;
		SDL_Rect m_SpriteSourceRect;
		int m_Rows, m_Cols;
		std::shared_ptr<Texture2D> m_Texture;
	};
}


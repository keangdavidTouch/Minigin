#pragma once
#include "Singleton.h"
#include <SDL.h>

struct SDL_Window;
struct SDL_Renderer;

namespace kd
{
	class Texture2D;

	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect* dst, const SDL_Rect* src = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE, const float rotation = 0.0f);
		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }

	private:
		SDL_Renderer* m_Renderer = nullptr;
	};
}


#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

void kd::Renderer::Init(SDL_Window * window)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void kd::Renderer::Render()
{
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(m_Renderer);
}

void kd::Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void kd::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dest;
	dest.x = static_cast<int>(x);
	dest.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dest.w, &dest.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dest);
}

void kd::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dest;
	dest.x = static_cast<int>(x);
	dest.y = static_cast<int>(y);
	dest.w = static_cast<int>(width);
	dest.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dest);
}

void kd::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect* dst, const SDL_Rect* src,
	SDL_RendererFlip flip, const float rotation)
{
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), src, dst, static_cast<double>(rotation), nullptr, flip);
}

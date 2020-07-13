#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
               
namespace kd
{
	struct SpriteInfo;

	class RenderComponent final : public BaseComponent 
	{
	public:
		RenderComponent();
		RenderComponent(std::shared_ptr<Texture2D> texture, SDL_Rect& srcDest);
		RenderComponent(const std::string& filename, SDL_Rect& srcDest);
		~RenderComponent();

		void Initialize() override;
		void Update() override;
		void Render() const override;

		void SetTexture(std::shared_ptr<Texture2D> texture);
		void SetSourceRect(SDL_Rect& src) { m_SrcRect = src; };
		void SetDestRect(SDL_Rect& dest) { m_DescRect = dest; };
	private:
		SDL_Rect m_SrcRect;
		SDL_Rect m_DescRect;
		std::shared_ptr<Texture2D> m_Texture;
	};
}


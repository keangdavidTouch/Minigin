#pragma once
#include "BaseComponent.h"
#include <SDL.h>

class Font;

namespace kd
{
	class TextComponent : public BaseComponent 
	{
	public:
		TextComponent(); 
		TextComponent(const std::string& textString, const std::string& fontName, int fontSize, SDL_Color color = {255,255,255});
		~TextComponent();

		void SetText(const std::string& textString);
		void SetFont(const std::string& fontName, int fontSize);
		void SetTextColor(SDL_Color color);

		void Initialize() override;
		void Update() override;
		void Render() const override;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		SDL_Color m_Color;
	};
}


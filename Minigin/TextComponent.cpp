#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "Time.h"

kd::TextComponent::TextComponent() 
	: m_Text("")
	, m_Font( nullptr )
	, m_NeedsUpdate( true )
	, m_Color{ 255,255,255 }
{
}

kd::TextComponent::TextComponent(const std::string& textString, const std::string& fontName, int fontSize, SDL_Color color)
	: m_Text(textString)
	, m_Font( nullptr )
	, m_NeedsUpdate( true )
	, m_Color{ color }
{
	m_Font = ResourceManager::GetInstance().LoadFont(fontName, fontSize); 
}

kd::TextComponent::~TextComponent()
{
}

void kd::TextComponent::Initialize()
{
}

void kd::TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);

		RenderComponent* renderer = GetGameObject()->GetComponent<RenderComponent>();
		renderer->SetTexture(std::make_shared<Texture2D>(texture));
	}
}

void kd::TextComponent::Render() const
{
}

void kd::TextComponent::SetText(const std::string& textString)
{
	m_Text = textString;
	m_NeedsUpdate = true;
}

void kd::TextComponent::SetFont(const std::string& fontName, int fontSize)
{
	m_Font = ResourceManager::GetInstance().LoadFont(fontName, fontSize);
	m_NeedsUpdate = true;
}

void kd::TextComponent::SetTextColor(SDL_Color color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}



#include "pch.h"
#include "TileRenderComponent.h"
#include "SpriteComponent.h"
#include "Renderer.h"
#include "SpriteSheetManager.h"

kd::TileRenderComponent::TileRenderComponent(const SpriteInfo& info, int cols, int rows) : m_Rows(rows), m_Cols(cols)
{
	m_SpriteSourceRect = SpriteSheetManager::GetInstance().GetSourceRect(info);
	m_Texture = SpriteSheetManager::GetInstance().GetTexture(0);
}

kd::TileRenderComponent::~TileRenderComponent()
{
	SafeDelete(m_SpriteSourceRect);

	for(auto desc : m_DescRects)
		SafeDelete(desc);
}

void kd::TileRenderComponent::Initialize()
{
	const auto pos = GetGameObject()->GetTransform().GetPosition();
	const auto scale = GetGameObject()->GetTransform().GetScale();
	auto desc = SDL_Rect();
	desc.x = static_cast<int>(pos.x);
	desc.y = static_cast<int>(pos.y);
	desc.w = static_cast<int>(m_SpriteSourceRect->w * scale.x);
	desc.h = static_cast<int>(m_SpriteSourceRect->h * scale.y);

	m_DescRects.reserve(m_Rows * m_Cols);

	for (int  i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Cols; j++)
		{
			m_DescRects.push_back(new SDL_Rect(desc));
			desc.x += desc.w;
		}

		desc.y += desc.h;
		desc.x = int(GetGameObject()->GetTransform().GetPosition().x);
	}
}

void kd::TileRenderComponent::Update()
{
}

void kd::TileRenderComponent::Render() const
{
	for (auto desc : m_DescRects)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, desc, m_SpriteSourceRect, static_cast<SDL_RendererFlip>(GetGameObject()->GetTransform().GetFlip()), GetGameObject()->GetTransform().GetRotation());
	}

}

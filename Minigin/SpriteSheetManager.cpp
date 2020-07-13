#include "MiniginPCH.h"
#include "SpriteSheetManager.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"

kd::SpriteSheetManager::SpriteSheetManager() : m_TextureMap{}
{
}

kd::SpriteSheetManager::~SpriteSheetManager()
{
}

std::shared_ptr<kd::Texture2D> kd::SpriteSheetManager::Load(const std::string & filename, int id)
{
	m_TextureMap[id] = ResourceManager::GetInstance().LoadTexture(filename);

	return m_TextureMap[id];
}

std::shared_ptr<kd::Texture2D> kd::SpriteSheetManager::GetTexture(int id)
{
	if (m_TextureMap[id])
		return m_TextureMap[id];

	return nullptr;
}

SDL_Rect kd::SpriteSheetManager::GetSourceRect(const SpriteInfo& info)
{
	SDL_Rect m_SrcRect = SDL_Rect();
	m_SrcRect.w = info.Rect.w;
	m_SrcRect.h = info.Rect.h;
	m_SrcRect.y = info.Rect.y;
	m_SrcRect.x = info.Rect.x + ((m_SrcRect.w + info.Offset) * info.StartFrameIndex) + info.Offset;
	
	return m_SrcRect;
}

void kd::SpriteSheetManager::GetSourceRectByRef(const SpriteInfo& info, SDL_Rect& srcRect)
{
	srcRect.w = info.Rect.w;
	srcRect.h = info.Rect.h;
	srcRect.y = info.Rect.y;
	srcRect.x = info.Rect.x + ((srcRect.w + info.Offset) * info.StartFrameIndex) + info.Offset;
}
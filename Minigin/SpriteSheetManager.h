#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <SDL.h>

namespace kd {
	struct SpriteInfo;

	class Texture2D;

	class SpriteSheetManager final : public Singleton<SpriteSheetManager>
	{
	public:
		SpriteSheetManager();
		~SpriteSheetManager();
		std::shared_ptr<kd::Texture2D> Load(const std::string& filename, int id);
		std::shared_ptr<Texture2D> GetTexture(int id);

		SDL_Rect GetSourceRect(const SpriteInfo& info);
		void GetSourceRectByRef(const SpriteInfo& info, SDL_Rect& srcRect);
	private:
		std::unordered_map<int, std::shared_ptr<Texture2D>> m_TextureMap;
	};
}




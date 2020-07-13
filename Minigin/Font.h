#pragma once
#include <SDL_ttf.h>

namespace kd
{
	class Font
	{
	public:
		TTF_Font* GetFont() const;
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;
	private:
		TTF_Font* mFont;
		unsigned int mSize;
	};

}

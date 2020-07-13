#include "MiniginPCH.h"
#include "Font.h"

TTF_Font* kd::Font::GetFont() const {
	return mFont;
}

kd::Font::Font(const std::string& fullPath, unsigned size) : mFont(nullptr), mSize(size)
{
	mFont = TTF_OpenFont(fullPath.c_str(), size);
	if (mFont == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

kd::Font::~Font()
{
	TTF_CloseFont(mFont);
}

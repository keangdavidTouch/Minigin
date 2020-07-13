#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

kd::Texture2D::Texture2D(SDL_Texture* texture)
{
	mTexture = texture;
}

SDL_Texture* kd::Texture2D::GetSDLTexture() const
{
	return mTexture;
}

kd::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(mTexture);
}
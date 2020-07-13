#pragma once
struct SDL_Texture;

namespace kd
{
	class Texture2D
	{
	public:
		explicit Texture2D(SDL_Texture* texture);
		SDL_Texture* GetSDLTexture() const;
		~Texture2D();

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;
	private:
		SDL_Texture* mTexture;
	};
}

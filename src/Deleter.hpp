#pragma once

#include <memory>

#include <SDL.h>
#include <SDL_image.h>

inline void TextureDeleter(SDL_Texture* texture)
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
	}
}

#include "Scenes.h"

Scenes::Scenes(SDL_Renderer* render)
	:m_render(render),
	background(IMG_LoadTexture(m_render, "assets/scenes/background.png"), TextureDeleter),
	graveyard(IMG_LoadTexture(m_render, "assets/scenes/graveyard.png")),
	mountains(IMG_LoadTexture(m_render, "assets/scenes/mountains.png")),
	tileset_sliced(IMG_LoadTexture(m_render, "assets/scenes/tileset-sliced.png"))
{
	SDL_GetRendererOutputSize(m_render, &renderW, &renderH);

	SDL_QueryTexture(background.get(), nullptr, nullptr, &backgroundW, &backgroundH);
	SDL_QueryTexture(graveyard, nullptr, nullptr, &graveyardW, &graveyardH);
	SDL_QueryTexture(mountains, nullptr, nullptr, &mountainsW, &mountainsH);
	SDL_QueryTexture(tileset_sliced, nullptr, nullptr, &tileset_slicedW, &tileset_slicedH);
}

Scenes::~Scenes()
{
	SDL_DestroyTexture(graveyard);
	SDL_DestroyTexture(mountains);
	SDL_DestroyTexture(tileset_sliced);
}

void Scenes::RenderBackground()
{
	{
		SDL_Rect sRect{ 0, 0, backgroundW, backgroundH };
		SDL_Rect dRect{ backgroundx, backgroundy, renderW * 1.8, renderH * 1.8 };
		SDL_RenderCopy(m_render, background.get(), &sRect, &dRect);
	}

	for (int i = -10; i < 10; i++)
	{
		int mountainsX = 300 * i - mountains_move;
		SDL_Rect sRect{ 0, 0, mountainsW, mountainsH };
		SDL_Rect dRect{ mountainsX, 180, mountainsW * 3, mountainsH * 3 };
		SDL_RenderCopy(m_render, mountains, &sRect, &dRect);
	}

	for (int i = -5; i < 5; i++)
	{
		int graveyardX = 1510 * i - graveyard_move;
		SDL_Rect sRect{ 0, 0, graveyardW, graveyardH };
		SDL_Rect dRect{ graveyardX, 250, graveyardW * 4, graveyardH * 4 };
		SDL_RenderCopy(m_render, graveyard, &sRect, &dRect);
	}
}

void Scenes::RenderForeground()
{
	for (int i = -30; i < 30; i++)
	{
		int tileset_slicedY = 180 * i - tileset_sliced_move;
		SDL_Rect sRect{ 64, 55, 64, 41 };
		SDL_Rect dRect{ tileset_slicedY, tileset_slicedy, 64 * 3, 41 * 3 };
		SDL_RenderCopy(m_render, tileset_sliced, &sRect, &dRect);
	}
}

void Scenes::setKeyboard(bool left, bool right)
{
	if (left)
	{
		if (backgroundx < -10)
		{
			backgroundx += 1;
		}
		mountains_move -= 2;
		graveyard_move -= 3;
		tileset_sliced_move -= 4;
	}
	if (right)
	{
		if (backgroundx > -885)
		{
			backgroundx -= 1;
		}
		mountains_move += 2;
		graveyard_move += 3;
		tileset_sliced_move += 4;
	}
}

void Scenes::setBlack()
{

}

void Scenes::setPillarHide()
{

}
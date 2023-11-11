#include "Scenes.h"

Scenes::Scenes(SDL_Renderer* render)
	:m_render(render),
	background(IMG_LoadTexture(m_render, "assets/scenes/background.png")),
	graveyard(IMG_LoadTexture(m_render, "assets/scenes/graveyard.png")),
	mountains(IMG_LoadTexture(m_render, "assets/scenes/mountains.png")),
	tileset_sliced(IMG_LoadTexture(m_render, "assets/scenes/tileset-sliced.png"))
{
	SDL_GetRendererOutputSize(m_render, &renderW, &renderH);
	SDL_QueryTexture(background, nullptr, nullptr, &backgroundW, &backgroundH);
	SDL_QueryTexture(graveyard, nullptr, nullptr, &graveyardW, &graveyardH);
	SDL_QueryTexture(mountains, nullptr, nullptr, &mountainsW, &mountainsH);
	SDL_QueryTexture(tileset_sliced, nullptr, nullptr, &tileset_slicedW, &tileset_slicedH);
}

Scenes::~Scenes()
{
	SDL_DestroyTexture(background);
}

void Scenes::task()
{
	SDL_Rect sRect{ 0, 0, backgroundW, backgroundH };
	SDL_Rect dRect{ tigerHeadx, tigerHeady, renderW * 1.7, renderH * 1.7 };
	SDL_RenderCopy(m_render, background, &sRect, &dRect);

	SDL_Rect s1Rect{ 300, 50, 400, 500 }; // tigerhead img
	SDL_Rect d1Rect{ -160, tigerHeady, 400, 500 };
	//SDL_RenderCopy(m_render, graveyard, &s1Rect, &d1Rect);
}

void Scenes::setKeyboard(bool left, bool right)
{
	if (left)
	{
		tigerHeadx += 5;
	}
	if (right)
	{
		tigerHeadx -= 5;
	}
}

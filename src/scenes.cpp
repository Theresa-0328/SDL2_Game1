#include "Scenes.h"

#include "Global.hpp"

Scenes::Scenes(SDL_Renderer* render)
	:m_render(render),
	background(IMG_LoadTexture(m_render, "assets/scenes/background.png")),
	graveyard(IMG_LoadTexture(m_render, "assets/scenes/graveyard.png")),
	mountains(IMG_LoadTexture(m_render, "assets/scenes/mountains.png")),
	tileset_sliced(IMG_LoadTexture(m_render, "assets/scenes/tileset-sliced.png")),
	isblack(false)
{
	SDL_GetRendererOutputSize(m_render, &renderW, &renderH);

	SDL_QueryTexture(background, nullptr, nullptr, &backgroundW, &backgroundH);
	SDL_QueryTexture(graveyard, nullptr, nullptr, &graveyardW, &graveyardH);
	SDL_QueryTexture(mountains, nullptr, nullptr, &mountainsW, &mountainsH);
	SDL_QueryTexture(tileset_sliced, nullptr, nullptr, &tileset_slicedW, &tileset_slicedH);

	blackSky = SDL_CreateTexture(m_render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1280, 720);
	SDL_SetTextureBlendMode(blackSky, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(m_render, blackSky);
	SDL_SetRenderDrawColor(m_render, 0, 0, 0, 255);
	SDL_RenderClear(m_render);
	SDL_SetRenderTarget(m_render, NULL);
}

Scenes::~Scenes()
{
	SDL_DestroyTexture(graveyard);
	SDL_DestroyTexture(mountains);
	SDL_DestroyTexture(tileset_sliced);
	SDL_DestroyTexture(blackSky);
	SDL_DestroyTexture(background);
}

void Scenes::RenderBackground()
{
	SDL_Rect sRect{ 0, 0, backgroundW, backgroundH };
	SDL_Rect dRect{ backgroundx, backgroundy, renderW * 1.8, renderH * 1.8 };
	SDL_RenderCopy(m_render, background, &sRect, &dRect);
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
	if (isblack || Grad)
	{
		SetBlackSkyAlpha();
		SDL_RenderCopy(m_render, blackSky, 0, 0);
	}

	SDL_Rect Pillar_sRect{ 224 ,48,32,96 };
	SDL_Rect PillarRect1{ Pillar_move, 430, Pillar_sRect.w * 3, Pillar_sRect.h * 3 };
	SDL_RenderCopy(m_render, tileset_sliced, &Pillar_sRect, &PillarRect1);
	SDL_Rect PillarRect2{ Pillar_move - 540, 430, Pillar_sRect.w * 3, Pillar_sRect.h * 3 };
	SDL_RenderCopy(m_render, tileset_sliced, &Pillar_sRect, &PillarRect2);
	PillarRect1_Collision.x = Pillar_move;

#ifdef SHOW_Rect
	SDL_SetRenderDrawColor(m_render, 255, 255, 0, 0xFF);
	SDL_RenderDrawRect(m_render, &PillarRect1_Collision);
#endif // SHOW_Rect
}

void Scenes::RenderForeground()
{
	for (int i = -30; i < 30; i++)
	{
		int tileset_slicedX = 180 * i - tileset_sliced_move;
		SDL_Rect sRect{ 64, 55, 64, 41 };
		SDL_Rect dRect{ tileset_slicedX, tileset_slicedy, sRect.x * 3, sRect.y * 3 };
		SDL_RenderCopy(m_render, tileset_sliced, &sRect, &dRect);
	}

#ifdef SHOW_Rect
	SDL_SetRenderDrawColor(m_render, 255, 255, 0, 0xFF);
	SDL_RenderDrawRect(m_render, &GroundCollision);
#endif // SHOW_Rect

}

void Scenes::setKeyboard(bool left, bool right)
{
	if (!getCanInput())
	{
		return;
	}
	if (left)
	{
		leftShiftScene();
	}
	if (right)
	{
		rightShiftScene();
	}
}

void Scenes::leftShiftScene()
{
	if (backgroundx < -10)
	{
		backgroundx += 1;
	}
	mountains_move -= 2;
	graveyard_move -= 3;
	tileset_sliced_move -= 4;

	Pillar_move += 4;
}

void Scenes::rightShiftScene()
{
	if (backgroundx > -885)
	{
		backgroundx -= 1;
	}
	mountains_move += 2;
	graveyard_move += 3;
	tileset_sliced_move += 4;

	Pillar_move -= 4;
}

void Scenes::setSkyState(bool isblack)
{
	this->isblack = isblack;
	Grad = true;
}

void Scenes::setPillarHide()
{

}

void Scenes::getPillarRectCollision(SDL_Rect& r1)
{
	r1 = PillarRect1_Collision;
}

void Scenes::SetBlackSkyAlpha()
{
	if (isblack)
	{
		BlackSkyAlpha += 5;
		if (BlackSkyAlpha >= 255)
			BlackSkyAlpha = 255;
	}
	else
	{
		BlackSkyAlpha -= 5;
		if (BlackSkyAlpha <= 0)
		{
			BlackSkyAlpha = 0;
			Grad = false;
		}
	}
	SDL_SetTextureAlphaMod(blackSky, BlackSkyAlpha);
}

#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Deleter.hpp"
class Scenes
{
public:
	Scenes(SDL_Renderer* render);
	~Scenes();
	void RenderBackground();
	void RenderForeground();
	void setKeyboard(bool left, bool right);
	void setSkyState(bool isblack);
	void setPillarHide();
private:
	SDL_Renderer* m_render;
	int renderW{};
	int renderH{};

	bool isblack;
	bool Grad{ false };

	SDL_Texture* blackSky{};
	SDL_Texture* background;
	int backgroundW{};
	int backgroundH{};

	SDL_Texture* graveyard;
	int graveyardW{};
	int graveyardH{};
	SDL_Texture* mountains;
	int mountainsW{};
	int mountainsH{};
	SDL_Texture* tileset_sliced;
	int tileset_slicedW{};
	int tileset_slicedH{};

	int backgroundx{ -450 };
	int backgroundy{ -230 };
	int mountains_move{};
	//int tileset_slicedx{ 600 };
	int tileset_slicedy{ 600 };
	int tileset_sliced_move{};
	int graveyardx{ -610 };
	int graveyardy{ 330 };
	int graveyard_move{};
	//SDL_HasIntersection

	void SetBlackSkyAlpha();
	int BlackSkyAlpha{ 0 };
	void leftShiftScene();
	void rightShiftScene();
};
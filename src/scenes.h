#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "Deleter.hpp"
#include "Base.h"

class Scenes :
	public Base
{
public:
	Scenes(SDL_Renderer* render);
	~Scenes();
	void RenderBackground();
	void RenderForeground();
	void setKeyboard(bool left, bool right);
	void setSkyState(bool isblack);
	void setPillarHide();
	std::vector<SDL_Rect> getScenesCollision()const;
	std::vector<SDL_Rect> getGroundCollision();
	void leftShiftScene(int offset = 0);
	void rightShiftScene(int offset = 0);
private:
	SDL_Renderer* m_render;
	int renderW{};
	int renderH{};

	bool isblack;
	bool Grad{ false };

	SDL_Texture* tree3{};
	SDL_Rect tree3Rect{ 0 ,285,350,339 };
	SDL_Texture* stone2{};
	SDL_Rect stone2Rect{ 329,533,55,82 };
	SDL_Texture* bush_large{};
	SDL_Rect bush_largeRect{ 487,491,155 ,132 };
	SDL_Texture* statue{};
	SDL_Rect statueRect{ 654,481 ,128,152 };
	SDL_Texture* stone4{};
	SDL_Rect stone4Rect{ 888,541,40,80 };
	SDL_Texture* tree2{};
	SDL_Rect tree2Rect{ 1089 ,375,382,270 };

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
	int Pillar_move{ 940 };
	int tileset_slicedy{ 600 };
	int tileset_sliced_move{};
	int graveyardx{ -610 };
	int graveyardy{ 330 };
	int graveyard_move{};

	void SetBlackSkyAlpha();
	int BlackSkyAlpha{ 0 };

	std::vector<SDL_Rect>ScenesCollision{ { 0, 625, 1280,87 } , { 940, 430, 96, 50 }, { 408, 430, 96, 50 } };
};
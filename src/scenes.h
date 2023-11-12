#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Scenes
{
public:
	Scenes(SDL_Renderer* render);
	~Scenes();
	void task();
	void setKeyboard(bool left, bool right);
private:
	SDL_Renderer* m_render;
	int renderW{};
	int renderH{};

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
};
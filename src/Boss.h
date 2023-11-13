#pragma once
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "Deleter.hpp"
class Boss
{
public:
	Boss(SDL_Renderer* render);
	~Boss();
	void task();
	void getInfo();
private:
	SDL_Renderer* m_render;
	int renderW{};
	int renderH{};

	SDL_RendererFlip human_flip = SDL_FLIP_NONE;

	int human_index = 0;
	int human_maxDuration = 150;
	int human_currentTime = SDL_GetTicks();
	int currentTime = SDL_GetTicks();
	int human_spriteChangeTime = human_currentTime + human_maxDuration;

	std::unique_ptr<SDL_Texture, decltype(&TextureDeleter)> Idle_img;
	int IdleW{};
	int IdleH{};
	std::vector<std::pair<int, int>> idle{ {0, 0}, {0, 1}, {0, 2}, {0, 3},{0, 4},{0, 5},{0, 6},{0, 7},{0, 8} };
	std::unique_ptr<SDL_Texture, decltype(&TextureDeleter)> Attack_img;
	std::vector<std::pair<int, int>> Attack{ {0, 0}, {0, 1}, {0, 2}, {0, 3},{0, 4},{0, 5},{0, 6},{0, 7},{0, 8},{0, 9}, {0, 10}, {0, 11}, {0, 12},{0, 13},{0, 14},{0, 15} };
	int AttackW{};
	int AttackH{};

	std::vector<std::pair<int, int>> current = Attack;
};
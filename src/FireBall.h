#pragma once
#include <vector>
# include <array>

#include "Deleter.hpp"
#include "Explosion.h"

class FireBall
{
public:
	FireBall(SDL_Renderer* render);
	~FireBall();
	void task();
	void getInfo();
	bool isExplosion(SDL_Rect rect2, int i);
private:
	SDL_Renderer* m_render;

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int index = 0;
	int maxDuration = 150;
	int currentTime = SDL_GetTicks();
	int spriteChangeTime = currentTime + maxDuration;

	std::shared_ptr<SDL_Texture> FireBall_move_img;
	std::vector<std::pair<int, int>> FireBall_move{ {0, 0}, {0, 1}, {0, 2}, {0, 3},{0, 4},{0, 5} };
	int FireBall_MoveW{};
	int FireBall_MoveH{};

	std::vector<std::pair<int, int>> current{ FireBall_move };
	std::shared_ptr<SDL_Texture> cur_ptr{ FireBall_move_img };

	std::vector<int> a1;
	Explosion* explosion;
};
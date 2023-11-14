#pragma once
#include <vector>

#include "Deleter.hpp"

class Explosion
{
public:
	Explosion(SDL_Renderer* render);
	~Explosion();
	void task();
	void setExp(int x, int y, int index);
private:
	SDL_Renderer* m_render;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	struct exp_index
	{
		exp_index(int x, int y, int index)
			:m_x(x),
			m_y(y),
			m_index(index)
		{
			currentTime = SDL_GetTicks();
			spriteChangeTime = currentTime + maxDuration;
		}
		int m_x;
		int m_y;
		int m_index;
		int maxDuration = 150;
		int currentTime;
		int spriteChangeTime;
	};
	std::vector<exp_index> bomb{};
	std::shared_ptr<SDL_Texture> Explosion_img;
	std::vector<std::pair<int, int>> Explosion_{ {0, 0}, {0, 1}, {0, 2}, {0, 3},{0, 4},{0, 5} };
};
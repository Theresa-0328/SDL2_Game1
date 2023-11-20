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
	void Render();
	void Update();
	bool isExplosion(SDL_Rect rect2, int i);
	bool start{ true };
private:
	SDL_Renderer* m_render;

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int index = 0;
	int maxDuration = 150;
	int currentTime = SDL_GetTicks();
	int spriteChangeTime = currentTime + maxDuration;

	std::shared_ptr<SDL_Texture> FireBall_move_img;
	const std::vector<int> FireBall_move{ 0,1,2,3,4,5 };

	const std::vector<int> current{ FireBall_move };
	std::shared_ptr<SDL_Texture> cur_ptr{ FireBall_move_img };

	std::vector<int> a1;
	Explosion* explosion;
};
#pragma once

#include <vector>
#include <array>
#include <iostream>

#include "Scenes.h"
#include "Deleter.hpp"

class FirePillar
{
public:
	FirePillar(SDL_Renderer* render);
	~FirePillar();
	void Start();
	void Render();
	void Update(Scenes* s);

private:
	SDL_Renderer* m_render;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	int LifeTime{};
	int FirePillarCd{};

	std::shared_ptr<SDL_Texture> FirePillar_img;
	const std::array<int, 2> FirePillar_vec{ 4,5 };

	std::shared_ptr<SDL_Texture> FirePillar_explosion_img;
	const std::array<int, 12> FirePillar_explosion_vec{ 0,1,2,3,4,5,7,8,9,10,11 };

	std::shared_ptr<SDL_Texture> FirePillar_move_img;
	const std::array<int, 3> FirePillar_move_vec{ 0,1,2 };

	void Move();
};
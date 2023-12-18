#pragma once

#include <vector>
#include <array>
#include <iostream>

#include "Boss.h"
#include "Deleter.hpp"

class FireBall
{
public:
	FireBall(SDL_Renderer* render);
	~FireBall();
	void Render();
	void Update(Boss* boss);
	void Start();
private:
	SDL_Renderer* m_render;

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	int index = 0;
	int maxDuration = 150;
	int currentTime = SDL_GetTicks();
	int ChangeTime = currentTime + maxDuration;

	std::shared_ptr<SDL_Texture> FireBall_move_img;
	const std::vector<int> FireBall_move_vec{ 0,1,2,3,4,5 };

	int Speed{};
	int Damage{};
	int LifeTime{};

	void Move();
	bool isExplosion(SDL_Rect rect2);

	bool bossDead;

	struct FireBallState
	{
		SDL_Rect FireBallLocation{};
		bool boom{ false };
		int index{};
		int currentTime{};
		int maxDuration{ 100 };
		int ChangeTime{ (int)SDL_GetTicks() + maxDuration };
		void updateIndex()
		{
			currentTime = SDL_GetTicks();
			if (currentTime > ChangeTime)
			{
				ChangeTime = currentTime + maxDuration;
				std::cout << index << "  " << currentTime << " " << ChangeTime << std::endl;
				index++;
			}
		}
	};
	std::array<FireBallState, 21> FBSGroup{};

	static constexpr int FireBallAttackTime{ 2400 };
	static constexpr int FireBallWaitTime{ 1300 };

	std::shared_ptr<SDL_Texture> Explosion_img;
	const std::vector<int> Explosion{ 0, 0, 1, 2, 3, 4, 5 ,6 };
};
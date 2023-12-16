#pragma once
#include <vector>
#include <array>

#include "Boss.h"
#include "Deleter.hpp"
#include "Explosion.h"

class FireBall
{
public:
	FireBall(SDL_Renderer* render);
	~FireBall();
	void Render();
	void Update(Boss* boss);
	bool isExplosion(SDL_Rect rect2, int i);
	void Start();
private:
	SDL_Renderer* m_render;

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	int index = 0;
	int maxDuration = 150;
	int currentTime = SDL_GetTicks();
	int ChangeTime = currentTime + maxDuration;

	std::shared_ptr<SDL_Texture> FireBall_move_img;
	const std::vector<int> FireBall_move{ 0,1,2,3,4,5 };

	const std::vector<int> current{ FireBall_move };
	std::shared_ptr<SDL_Texture> cur_ptr{ FireBall_move_img };

	std::vector<int> a1;
	Explosion* explosion;

	int Speed{};
	int Damage{};
	int LifeTime{};

	void Move();

	bool bossDead;
	static constexpr int FireBallInitX{ 140 };
	SDL_Rect dRect1 = { FireBallInitX, 450, 160, 160 };
	SDL_Rect dRect2 = { FireBallInitX, 450, 160, 160 };
	SDL_Rect dRect3 = { FireBallInitX, 450, 160, 160 };

	static constexpr int FireBallAttackTime{ 2400 };
	static constexpr int FireBallWaitTime{ 1300 };

};
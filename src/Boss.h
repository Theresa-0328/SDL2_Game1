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

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int index = 0;
	int maxDuration = 150;
	int currentTime = SDL_GetTicks();
	int spriteChangeTime = currentTime + maxDuration;

	std::shared_ptr<SDL_Texture> Idle_img;
	std::vector<std::pair<int, int>> idle{ {0, 0}, {0, 1}, {0, 2}, {0, 3},{0, 4},{0, 5},{0, 6},{0, 7},{0, 8} };
	int IdleW{};
	int IdleH{};

	std::shared_ptr<SDL_Texture> Attack_img;
	std::vector<std::pair<int, int>> Attack{ {0, 0}, {0, 1}, {0, 2}, {0, 3},{0, 4},{0, 5},{0, 6},{0, 7},{0, 8},{0, 9}, {0, 10}, {0, 11}, {0, 12},{0, 13},{0, 14},{0, 15} };
	int AttackW{};
	int AttackH{};

	std::shared_ptr<SDL_Texture> Death_img;
	std::vector<std::pair<int, int>> Death{ {0, 0}, {0, 1}, {0, 2}, {0, 3},{0, 4},{0, 5},{0, 6},{0, 7} };
	int DeathW{};
	int DeathH{};

	std::shared_ptr<SDL_Texture> Walk_img;
	std::vector<std::pair<int, int>> Walk{ {0, 0}, {0, 1}, {0, 2}, {0, 3},{0, 4},{0, 5},{0, 6},{0, 7},{0, 8} };
	int WalkW{};
	int WalkH{};

	std::shared_ptr<SDL_Texture> Get_Hit_img;
	std::vector<std::pair<int, int>> Get_Hit{ {0, 0}, {0, 1}, {0, 2}, {0, 3},{0, 4},{0, 5},{0, 6},{0, 7},{0, 8} };
	int Get_HitW{};
	int Get_HitH{};

	std::vector<std::pair<int, int>> current = idle;
	std::shared_ptr<SDL_Texture> cur_ptr = Idle_img;

	enum BossState
	{
		_FireBall,
		_FirePillar,
		_Dash,
		_Idle,
		_BeHit,
		_Death,
	};

	int a = 0;
	void UpdateBossState(BossState state);
	void FireBallSkill();
	void IdleProccess();
	void DeathProccess();
	void DashSkill();
	void BeHitProccess();
	void FirePillarSkill();
};
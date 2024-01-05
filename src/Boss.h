#pragma once

#include <vector>
#include <array>

#include <SDL.h>
#include <SDL_image.h>

#include "Deleter.hpp"
#include "Scenes.h"
#include "FireBall.h"
#include "FirePillar.h"
#include "Global.hpp"

class Boss :
	public Base
{
public:
	Boss(SDL_Renderer* render, Scenes* scenes);
	~Boss();
	enum BossState
	{
		_FireBall,
		_FirePillar,
		_Dash,
		_Idle,
		_BeHit,
		_Death,
	};
	void Init(UI* ui, Player* player, FireBall* fireBall, FirePillar* firePillar);
	void Render();
	void update();
	BossState getBossStart() const;
	void setKeyboard(bool left, bool right);
	SDL_Rect bossLocation{ 0, 360, 400, 400 };
	int index = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	void setFireCanInput(bool isCanInput);
	void setHp(int hp);
	int getHp() const;
private:
	bool isDead{ false };
	bool isHit{ false };

	SDL_Renderer* m_render;
	Scenes* m_scenes;
	FireBall* m_fireBall;
	FirePillar* m_firePillar;
	UI* m_ui;
	Player* m_player;


	int renderW{};
	int renderH{};

	int maxDuration = 150;
	int currentTime = SDL_GetTicks();
	int ChangeTime = currentTime + maxDuration;

	std::shared_ptr<SDL_Texture> Idle_img;
	const std::vector<int> idle{ 0,1,2,3,4,5,6,7,8 };

	std::shared_ptr<SDL_Texture> Attack_img;
	const std::vector<int> Attack{ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };

	std::shared_ptr<SDL_Texture> Death_img;
	const std::vector<int> Death{ 0,1,2,3,4,5,6,7 };

	std::shared_ptr<SDL_Texture> Walk_img;
	const std::vector<int> Walk{ 0,1,2,3,4,5,6,7,8 };

	std::shared_ptr<SDL_Texture> Get_Hit_img;
	const std::vector<int> Get_Hit{ 0,1,2,3,4,5,6,7,8 };

	std::vector<int> current{ idle };
	std::shared_ptr<SDL_Texture> cur_ptr{ Idle_img };

	int MaxHp{ 200 };
	BossState m_boss_state = BossState::_Idle;

	void UpdateBossState(BossState state);
	void FireBallSkill();
	void IdleProccess();
	void DeathProccess();
	void DashSkill();
	void BeHitProccess();
	void FirePillarSkill();

	uint64_t FirePillarAttackTime{};
	uint64_t FireBallAttackTime{};
	uint64_t DashSkillTime{};
	uint64_t IdleTime{ 2500 + SDL_GetTicks() };
	uint64_t FirePillarCd{ SDL_GetTicks() + 15000 };

	void leftShiftBoss();
	void rightShiftBoss();

	static const int MAX_HP{ 100 };
	int Hp{ 100 };
	void UpdateBossHp();
	void BeHit(int Damge);
};
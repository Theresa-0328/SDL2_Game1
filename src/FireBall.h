#pragma once

#include <vector>
#include <array>
#include <iostream>

#include "Ui.h"
#include "Global.hpp"
#include "Scenes.h"

class Boss;
class Player;

class FireBall :
	public Base
{
public:
	FireBall(SDL_Renderer* render);
	~FireBall();
	void Init(Scenes* s, UI* ui, Boss* boss, Player* player);
	void Render();
	void Update();
	void Start();
	void setKeyboard(bool left, bool right);
	void leftShiftFireBall(int offset = 0);
	void rightShiftFireBall(int offset = 0);
private:
	SDL_Renderer* m_render;
	Player* m_player;
	Boss* m_boss;
	Scenes* m_scenes;
	UI* m_ui;

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
	void checkExplosion();

	struct FireBallState
	{
		FireBallState(SDL_Rect rect, int angle) :
			FireBallLocation(rect),
			m_angle(angle),
			InitLocation(rect)
		{
		}
		SDL_Rect FireBallLocation{};
		SDL_Rect InitLocation{};
		bool boom{ false };
		int index{};
		int currentTime{};
		int maxDuration{ 100 };
		int ChangeTime{ (int)SDL_GetTicks() + maxDuration };
		int m_angle{};
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
	std::vector<FireBallState> FBSGroup{};

	static constexpr int FireBallAttackTime{ 2400 };
	static constexpr int FireBallWaitTime{ 1300 };

	std::shared_ptr<SDL_Texture> Explosion_img;
	const std::vector<int> Explosion{ 0, 0, 1, 2, 3, 4, 5 ,6 };
	void addFireBall(int num = 7);
	int waves{ 0 };
};
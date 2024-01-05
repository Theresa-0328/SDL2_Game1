#pragma once

#include <vector>
#include <array>
#include <iostream>

#include "Scenes.h"
#include "Deleter.hpp"

class Boss;
class Player;

class FirePillar :
	public Base
{
public:
	FirePillar(SDL_Renderer* render);
	~FirePillar();
	void Init(Boss* boss);
	void Start();
	void Render();
	void Update(Boss* boss);
	void setKeyboard(bool left, bool right);
private:
	SDL_Renderer* m_render;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	int LifeTime{};

	std::shared_ptr<SDL_Texture> FirePillar_move_img;
	const std::array<int, 3> FirePillar_move_vec{ 0,1,2 };
	std::shared_ptr<SDL_Texture> FirePillar_img;
	const std::array<int, 2> FirePillar_vec{ 4,5 };
	std::shared_ptr<SDL_Texture> FirePillar_explosion_img;
	const std::array<int, 6> FirePillar_explosion_vec{ 0,1,2,3,4,5 };

	void Move();

	struct FirePillarState
	{
		SDL_Rect Location{};
		enum State
		{
			move = 0,
			explosion = 1,
			pillar = 2
		};
		uint32_t lifeTime{ 0 };
		State state{ move };
		bool stop{ false };
		int index;
		int vec_size;
		int currentTime{};
		int maxDuration{ 100 };
		int ChangeTime{ (int)SDL_GetTicks() + maxDuration };

		FirePillarState(SDL_Rect l, State s) :
			Location(l),
			state(s),
			index(0),
			vec_size(0)
		{
		}

		void updateIndex()
		{
			currentTime = SDL_GetTicks();
			if (currentTime > ChangeTime)
			{
				ChangeTime = currentTime + maxDuration;
				std::cout << index << "  " << currentTime << " " << ChangeTime << std::endl;
				index++;
				if (index >= vec_size)
				{
					index = 0;
				}
			}
		}
	};
	std::vector<FirePillarState*> FBSGroup{};
	int Speed{ 0 };
	void addFirePillar(int num = 7);
	int waves{ 0 };

	void leftShiftFirePillar();
	void rightShiftFirePillar();

	Boss* m_boss{};
};
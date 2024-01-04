#pragma once

#include "Deleter.hpp"

class UI
{
public:
	UI(SDL_Renderer* render);
	~UI();
	void Init();
	void Update();
	void Render();
	void setPlayerHpValue(int value, int min1 = 0, int max1 = 100, int min2 = 0, int max2 = 256);
	void setBossHpValue(int value, int min1 = 0, int max1 = 100, int min2 = 0, int max2 = 447);
private:
	SDL_Renderer* m_render;
	SDL_Texture* rpg1;
	SDL_Texture* rpg2;
	SDL_Texture* rpg3;

	SDL_Rect Player2Hp_img{ 33,114,80,9 };
	SDL_Rect BossHp_img{ 33,126,80,9 };
	SDL_Rect Health_img{ 40,84,66,7 };

	int BossHp_img_w{ 447 };
	int PlayHp_img_w{ 256 };
};
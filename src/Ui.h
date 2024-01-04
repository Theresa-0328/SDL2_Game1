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
private:
	SDL_Renderer* m_render;
	SDL_Texture* rpg1;
	SDL_Texture* rpg2;
	SDL_Texture* rpg3;

	SDL_Rect Player2Hp_img{ 33,114,80,9 };
	SDL_Rect BossHp_img{ 33,126,80,9 };
	SDL_Rect Health_img{ 40,84,66,7 };
};
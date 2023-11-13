#include "Player.h"

Player::Player(SDL_Renderer* render)
	:m_render(render),
	player2(IMG_LoadTexture(render, "assets/player/player2.png"))
{
	SDL_GetRendererOutputSize(m_render, &renderW, &renderH);
}

Player::~Player()
{

}

void Player::task()
{
	if (human_index >= current.size())
	{
		human_index = 0;
	}

	SDL_Rect sRect = { current[human_index].second * widthSpr, current[human_index].first * heightSpr, widthSpr, heightSpr };
	SDL_Rect dRect = { player2_x, player2_y, imgW, imgH };
	SDL_RenderCopyEx(m_render, player2, &sRect, &dRect, 0, nullptr, human_flip);

	currentTime = SDL_GetTicks();
	if (currentTime > human_spriteChangeTime)
	{
		human_spriteChangeTime += human_maxDuration;
		human_index++;
		if (human_index >= current.size())
		{
			human_index = 0;
			//current = idle2;
		}
	}
}

void Player::setKeyboard(bool left, bool right, bool J)
{
	if (left)
	{
		current = run;
		human_flip = SDL_FLIP_HORIZONTAL;
	}
	if (right)
	{
		current = run;
		human_flip = SDL_FLIP_NONE;
	}
	if (J)
	{
		current = attack1;
	}
	if (!left && !right && !J)
	{
		current = idle2;
	}
}

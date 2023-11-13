#include "Boss.h"

Boss::Boss(SDL_Renderer* render)
	:m_render(render),
	Idle_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Idle.png"), TextureDeleter),
	Attack_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Attack.png"), TextureDeleter)
{
	SDL_GetRendererOutputSize(m_render, &renderW, &renderH);

	SDL_QueryTexture(Idle_img.get(), nullptr, nullptr, &IdleW, &IdleH);
	SDL_QueryTexture(Attack_img.get(), nullptr, nullptr, &AttackW, &AttackH);
}

Boss::~Boss()
{
}

void Boss::task()
{
	SDL_Rect sRect = { current[human_index].second * 90, current[human_index].first * 90, 90,90 };
	SDL_Rect dRect = { 0, 440, 280, 280 };
	SDL_RenderCopy(m_render, Attack_img.get(), &sRect, &dRect);

	currentTime = SDL_GetTicks();
	if (currentTime > human_spriteChangeTime)
	{
		human_spriteChangeTime += human_maxDuration;
		human_index++;
		if (human_index >= current.size())
		{
			human_index = 0;
			current = Attack;
		}
	}
}
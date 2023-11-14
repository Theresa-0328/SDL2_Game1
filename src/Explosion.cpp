#include "Explosion.h"

Explosion::Explosion(SDL_Renderer* render)
	:m_render(render),
	Explosion_img(IMG_LoadTexture(m_render, "assets/Boss/Fire Ball/Explosion.png"), TextureDeleter)
{
}

Explosion::~Explosion()
{

}

void Explosion::task()
{
	for (auto it = bomb.begin(); it != bomb.end(); it++)
	{
		if (it->m_index >= Explosion_.size())
		{
			continue;
		}
		SDL_Rect sRect = { Explosion_[it->m_index].second * 46, 0, 46,46 };
		SDL_Rect dRect = { it->m_x, it->m_y, 160, 160 };
		SDL_RenderCopyEx(m_render, Explosion_img.get(), &sRect, &dRect, 0, nullptr, flip);
		it->currentTime = SDL_GetTicks();
		if (it->currentTime > it->spriteChangeTime)
		{
			it->spriteChangeTime += it->maxDuration;
			it->m_index++;
		}
	}
}

void Explosion::setExp(int x, int y, int index)
{
	bomb.push_back({ x, y, index });
}
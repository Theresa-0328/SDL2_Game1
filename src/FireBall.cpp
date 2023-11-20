#include "FireBall.h"


FireBall::FireBall(SDL_Renderer* render)
	:m_render(render),
	FireBall_move_img(IMG_LoadTexture(m_render, "assets/Boss/Fire Ball/Move.png"), TextureDeleter)
{
	explosion = new Explosion(m_render);
}

FireBall::~FireBall()
{
	delete explosion;
}

int a = 0;
void FireBall::Render()
{
	if (start)
		return;
	for (int i = -1; i < 6; i++)
	{
		SDL_Rect sRect = { current[index] * 46, 0, 46,46 };
		SDL_Rect dRect = { 180 + a * 5, 830 - (380 + a * i), 160, 160 };
		if (std::find(a1.begin(), a1.end(), i) != a1.end())
		{
			continue;
		}
		if (isExplosion(dRect, i))
		{
			explosion->setExp(100 + a * 5, 800 - (380 + a * i), 0);
		}
		SDL_RenderCopyEx(m_render, FireBall_move_img.get(), &sRect, &dRect, -15 * i, nullptr, flip);
		currentTime = SDL_GetTicks();
		if (currentTime > spriteChangeTime)
		{
			spriteChangeTime += maxDuration;
			index++;
			if (index >= current.size())
			{
				index = 0;
			}
		}
	}
	a++;
	if (a * 5 > 1300)
	{
		a = 0;
		a1.clear();
	}
	explosion->task();
}

void FireBall::Update()
{

}

bool FireBall::isExplosion(SDL_Rect rect2, int i)
{
	SDL_Rect rect1{ 0, 700, 1280, 10 };
	if (SDL_HasIntersection(&rect1, &rect2))
	{
		a1.push_back(i);
		return true;
	}
	return false;
}

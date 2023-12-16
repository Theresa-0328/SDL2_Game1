#include "FireBall.h"


FireBall::FireBall(SDL_Renderer* render) :
	m_render(render),
	FireBall_move_img(IMG_LoadTexture(m_render, "assets/Boss/Fire Ball/Move.png"), TextureDeleter),
	bossDead(false)
{
	explosion = new Explosion(m_render);
}

FireBall::~FireBall()
{
	delete explosion;
}

void FireBall::Render()
{
	if (LifeTime <= SDL_GetTicks() || bossDead)
	{
		return;
	}
	Move();
	//for (int i = -1; i < 6; i++)
	//{
	//	SDL_Rect sRect = { current[index] * 46, 0, 46,46 };

	//	//if (std::find(a1.begin(), a1.end(), i) != a1.end())
	//	//{
	//	//	continue;
	//	//}
	//	//if (isExplosion(dRect, i))
	//	//{
	//	//	explosion->setExp(100 + a * 5, 800 - (380 + a * i), 0);
	//	//}
	SDL_Rect sRect = { current[index] * 46, 0, 46,46 };
	if (LifeTime < FireBallAttackTime * 5 - FireBallWaitTime + SDL_GetTicks())
	{
		SDL_RenderCopyEx(m_render, FireBall_move_img.get(), &sRect, &dRect1, 0, nullptr, flip);
	}
	if (LifeTime < FireBallAttackTime * 4 - FireBallWaitTime + SDL_GetTicks())
	{
		SDL_RenderCopyEx(m_render, FireBall_move_img.get(), &sRect, &dRect2, 0, nullptr, flip);
	}
	if (LifeTime < FireBallAttackTime * 3 - FireBallWaitTime + SDL_GetTicks())
	{
		SDL_RenderCopyEx(m_render, FireBall_move_img.get(), &sRect, &dRect3, 0, nullptr, flip);
	}
	currentTime = SDL_GetTicks();
	if (currentTime > ChangeTime)
	{
		ChangeTime += maxDuration;
		index++;
		if (index >= current.size())
		{
			index = 0;
		}
	}
	//explosion->task();
}

void FireBall::Update(Boss* boss)
{
	if (boss->getBossStart() == Boss::_FireBall && LifeTime <= SDL_GetTicks())
	{
		Start();
	}
	if (boss->getBossStart() == Boss::_Death)
	{
		LifeTime = 0;
	}
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

void FireBall::Start()
{
	Speed = 7;
	//Damage = 8;
	LifeTime = FireBallAttackTime * 5 + SDL_GetTicks();
	dRect1.x = FireBallInitX;
	dRect2.x = FireBallInitX;
	dRect3.x = FireBallInitX;
}

void FireBall::Move()
{
	uint32_t time = SDL_GetTicks();
	if (flip)
	{

	}
	else
	{
		if (LifeTime < FireBallAttackTime * 5 - FireBallWaitTime + time)
		{
			dRect1.x = dRect1.x + Speed;
		}
		if (LifeTime < FireBallAttackTime * 4 - FireBallWaitTime + time)
		{
			dRect2.x = dRect2.x + Speed;
		}
		if (LifeTime < FireBallAttackTime * 3 - FireBallWaitTime + time)
		{
			dRect3.x = dRect3.x + Speed;
		}
	}
}
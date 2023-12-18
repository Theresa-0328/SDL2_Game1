#include "FireBall.h"

#include <cmath>

struct Point
{
	double x;
	double y;
};

Point rotatePoint(const Point& A, const Point& B, double angle) {
	double theta = angle * M_PI / 180.0;
	double x_C = cos(theta) * (B.x - A.x) - sin(theta) * (B.y - A.y) + A.x;
	double y_C = sin(theta) * (B.x - A.x) + cos(theta) * (B.y - A.y) + A.y;
	return { x_C, y_C };
}

/*------------------------------------*/

FireBall::FireBall(SDL_Renderer* render) :
	m_render(render),
	FireBall_move_img(IMG_LoadTexture(m_render, "assets/Boss/Fire Ball/Move.png"), TextureDeleter),
	bossDead(false),
	Explosion_img(IMG_LoadTexture(m_render, "assets/Boss/Fire Ball/Explosion.png"), TextureDeleter)
{

}

FireBall::~FireBall()
{

}

void FireBall::Render()
{
	if (LifeTime <= SDL_GetTicks() || bossDead)
	{
		return;
	}
	for (int i{ 0 }; i < 21; i++)
	{
		FBSGroup[i].boom = isExplosion(FBSGroup[i].FireBallLocation);
	}
	Move();
	SDL_Rect sRect = { current[index] * 46, 0, 46,46 };
	if (LifeTime < FireBallAttackTime * 5 - FireBallWaitTime + SDL_GetTicks())
	{
		for (int i{ 0 }; i < 7; i++)
		{
			if (FBSGroup[i].index > 7)
			{
				continue;
			}
			if (FBSGroup[i].boom == true)
			{
				SDL_SetRenderDrawColor(m_render, 0, 0, 255, 0xFF);
				SDL_RenderDrawRect(m_render, &FBSGroup[i].FireBallLocation);

				SDL_Rect sRect = { Explosion[FBSGroup[i].index] * 46, 0, 46,46 };
				SDL_RenderCopyEx(m_render, Explosion_img.get(), &sRect, &FBSGroup[i].FireBallLocation, 0, nullptr, flip);
				FBSGroup[i].updateIndex();
				continue;
			}
			SDL_RenderCopyEx(m_render, FireBall_move_img.get(), &sRect, &FBSGroup[i].FireBallLocation, (i - 1) * -15, nullptr, flip);
			//std::cout << i << " x " << dRect1.x << " y " << dRect1.y << std::endl;
		}
	}
	if (LifeTime < FireBallAttackTime * 4 - FireBallWaitTime + SDL_GetTicks())
	{
		for (int i{ 7 }; i < 14; i++)
		{
			if (FBSGroup[i].index > 7)
			{
				continue;
			}
			if (FBSGroup[i].boom == true)
			{
				SDL_SetRenderDrawColor(m_render, 0, 0, 255, 0xFF);
				SDL_RenderDrawRect(m_render, &FBSGroup[i].FireBallLocation);

				SDL_Rect sRect = { Explosion[FBSGroup[i].index] * 46, 0, 46,46 };
				SDL_RenderCopyEx(m_render, Explosion_img.get(), &sRect, &FBSGroup[i].FireBallLocation, 0, nullptr, flip);
				FBSGroup[i].updateIndex();
				continue;
			}
			SDL_RenderCopyEx(m_render, FireBall_move_img.get(), &sRect, &FBSGroup[i].FireBallLocation, (i - 8) * -15, nullptr, flip);
		}
	}
	if (LifeTime < FireBallAttackTime * 3 - FireBallWaitTime + SDL_GetTicks())
	{
		for (int i{ 14 }; i < 21; i++)
		{
			if (FBSGroup[i].index > 7)
			{
				continue;
			}
			if (FBSGroup[i].boom == true)
			{
				SDL_SetRenderDrawColor(m_render, 0, 0, 255, 0xFF);
				SDL_RenderDrawRect(m_render, &FBSGroup[i].FireBallLocation);

				SDL_Rect sRect = { Explosion[FBSGroup[i].index] * 46, 0, 46,46 };
				SDL_RenderCopyEx(m_render, Explosion_img.get(), &sRect, &FBSGroup[i].FireBallLocation, 0, nullptr, flip);
				FBSGroup[i].updateIndex();
				continue;
			}
			SDL_RenderCopyEx(m_render, FireBall_move_img.get(), &sRect, &FBSGroup[i].FireBallLocation, (i - 15) * -15, nullptr, flip);
		}
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

bool FireBall::isExplosion(SDL_Rect rect2)
{
	SDL_Rect rect1{ 0, 700, 1280, 10 };
	SDL_SetRenderDrawColor(m_render, 255, 255, 0, 0xFF);
	SDL_RenderDrawRect(m_render, &rect1);
	if (SDL_HasIntersection(&rect1, &rect2))
	{
		return true;
	}
	rect1.x = 640;
	rect1.y = 480;
	rect1.w = 100;
	rect1.h = 100;
	SDL_SetRenderDrawColor(m_render, 255, 255, 0, 0xFF);
	SDL_RenderDrawRect(m_render, &rect1);
	if (SDL_HasIntersection(&rect1, &rect2))
	{
		return true;
	}
	return false;
}

void FireBall::Start()
{
	Speed = 7;
	Damage = 8;
	LifeTime = FireBallAttackTime * 5 + SDL_GetTicks();
	for (int i{ 0 }; i < 21; i++)
	{
		FBSGroup[i] = { { 140, 450, 185,185 } ,0 ,0 };
	}
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
			for (int i{ 0 }; i < 7; i++)
			{
				if (FBSGroup[i].boom == true)
				{
					continue;
				}
				FBSGroup[i].FireBallLocation.x += Speed;
				Point C = rotatePoint({ 140,450 }, { (double)FBSGroup[i].FireBallLocation.x,450 }, (i - 1) * -15);
				FBSGroup[i].FireBallLocation.y = C.y;
			}
		}
		if (LifeTime < FireBallAttackTime * 4 - FireBallWaitTime + time)
		{
			for (int i{ 7 }; i < 14; i++)
			{
				if (FBSGroup[i].boom == true)
				{
					continue;
				}
				FBSGroup[i].FireBallLocation.x += Speed;
				Point C = rotatePoint({ 140,450 }, { (double)FBSGroup[i].FireBallLocation.x,450 }, (i - 8) * -15);
				FBSGroup[i].FireBallLocation.y = C.y;
			}
		}
		if (LifeTime < FireBallAttackTime * 3 - FireBallWaitTime + time)
		{
			for (int i{ 14 }; i < 21; i++)
			{
				if (FBSGroup[i].boom == true)
				{
					continue;
				}
				FBSGroup[i].FireBallLocation.x += Speed;
				Point C = rotatePoint({ 140,450 }, { (double)FBSGroup[i].FireBallLocation.x,450 }, (i - 15) * -15);
				FBSGroup[i].FireBallLocation.y = C.y;
			}
		}
	}
}
#include "FireBall.h"

#include <cmath>

#include "Global.hpp"

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
	Explosion_img(IMG_LoadTexture(m_render, "assets/Boss/Fire Ball/Explosion.png"), TextureDeleter),
	m_boss(nullptr)
{

}

FireBall::~FireBall()
{

}

void FireBall::Init(Boss* boss)
{
	m_boss = boss;
}

void FireBall::Render()
{
	if (LifeTime <= SDL_GetTicks())
	{
		return;
	}
	Move();
	isExplosion();
	for (int i{ 0 }; i < FBSGroup.size(); i++)
	{
		if (FBSGroup[i].boom)
		{
			SDL_Rect sRect = { Explosion[FBSGroup[i].index] * 46, 0, 46,46 };
			SDL_RenderCopyEx(m_render, Explosion_img.get(), &sRect, &FBSGroup[i].FireBallLocation, 0, nullptr, flip);
			FBSGroup[i].updateIndex();
		}
		else
		{
			SDL_Rect sRect = { FireBall_move_vec[index] * 46, 0, 46,46 };
			SDL_RenderCopyEx(m_render, FireBall_move_img.get(), &sRect, &FBSGroup[i].FireBallLocation, FBSGroup[i].m_angle, nullptr, flip);
		}
#ifdef SHOW_Rect
		SDL_SetRenderDrawColor(m_render, 0, 0, 255, 0xFF);
		SDL_RenderDrawRect(m_render, &FBSGroup[i].FireBallLocation);
#endif
	}
	currentTime = SDL_GetTicks();
	if (currentTime > ChangeTime)
	{
		ChangeTime += maxDuration;
		index++;
		if (index >= FireBall_move_vec.size())
		{
			index = 0;
		}
	}
}

void FireBall::Update()
{
	if (m_boss->getBossStart() == Boss::_Death)
	{
		LifeTime = 0;
		return;
	}
	if (m_boss->getBossStart() != Boss::_FireBall)
	{
		return;
	}
	if (LifeTime <= SDL_GetTicks())
	{
		Start();
	}
	if (LifeTime <= SDL_GetTicks() - FireBallWaitTime + FireBallAttackTime * 5 && waves == 0)
	{
		addFireBall();
		waves = 1;
	}
	if (LifeTime <= SDL_GetTicks() - FireBallWaitTime + FireBallAttackTime * 4 && waves == 1)
	{
		addFireBall();
		waves = 2;
	}
	if (LifeTime <= SDL_GetTicks() - FireBallWaitTime + FireBallAttackTime * 3 && waves == 2)
	{
		addFireBall();
		waves = 3;
	}
	//std::cout << "FireBall::Update" << LifeTime << " " << SDL_GetTicks() - FireBallWaitTime + FireBallAttackTime * 5 << std::endl;
}

void FireBall::isExplosion()
{
	for (auto& it : FBSGroup)
	{
		if (it.boom)
		{
			continue;
		}
		if (SDL_HasIntersection(&GroundCollision, &it.FireBallLocation))
		{
			it.boom = true;
			it.index = 0;
		}
		if (SDL_HasIntersection(&PlayerCollision, &it.FireBallLocation))
		{
			it.boom = true;
			it.index = 0;
		}
	}
}

void FireBall::leftShiftFireBall()
{
	for (auto& it : FBSGroup)
	{
		it.FireBallLocation.x += 4;
	}
}

void FireBall::rightShiftFireBall()
{
	for (auto& it : FBSGroup)
	{
		it.FireBallLocation.x -= 4;
	}
}

void FireBall::addFireBall(int num)
{
	for (int i{ 0 }; i < 7; i++)
	{
		//SDL_RendererFlip
		FBSGroup.push_back({ { m_boss->bossLocation.x + 225, 430, 185,185 } ,(i - 1) * -15 });
	}
}

void FireBall::Start()
{
	Speed = 7;
	Damage = 8;
	LifeTime = FireBallAttackTime * 5 + SDL_GetTicks();
	FBSGroup.clear();
	waves = 0;
}

void FireBall::setKeyboard(bool left, bool right)
{
	if (left)
	{
		leftShiftFireBall();
	}
	if (right)
	{
		rightShiftFireBall();
	}
}

void FireBall::Move()
{
	for (int i{ 0 }; i < FBSGroup.size(); i++)
	{
		if (FBSGroup[i].index >= 8)
		{
			std::swap(FBSGroup[i], FBSGroup.back());
			FBSGroup.pop_back();
			i--;
		}
		if (i < 0)
			continue;
		//std::cout << "FBSGroup.pop_back();  " << i << " " << FBSGroup[i].index << std::endl;
	}
	uint32_t time = SDL_GetTicks();
	if (flip)
	{

	}
	else
	{
		for (int i{ 0 }; i < FBSGroup.size(); i++)
		{
			if (FBSGroup[i].boom)
			{
				continue;
			}
			FBSGroup[i].FireBallLocation.x += Speed;
			Point C = rotatePoint({ (double)FBSGroup[i].InitLocation.x,(double)FBSGroup[i].InitLocation.y }, { (double)FBSGroup[i].FireBallLocation.x,450 }, FBSGroup[i].m_angle);
			FBSGroup[i].FireBallLocation.y = C.y;
		}
	}
}
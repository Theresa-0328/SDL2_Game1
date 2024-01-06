#include "FireBall.h"

#include <cmath>

#include "Global.hpp"
#include "Player.h"
#include "Boss.h"

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
	m_ui(nullptr)
{
}

FireBall::~FireBall()
{

}

void FireBall::Init(Scenes* s, UI* ui, Boss* boss, Player* player)
{
	m_boss = boss;
	m_player = player;
	m_ui = ui;
	m_scenes = s;
}

void FireBall::Render()
{
	if (LifeTime <= SDL_GetTicks())
	{
		return;
	}
	Move();
	checkExplosion();
	for (int i{ 0 }; i < FBSGroup.size(); i++)
	{
		if (FBSGroup[i].boom)
		{
			SDL_Rect sRect = { Explosion[FBSGroup[i].index] * 46, 0, 46,46 };
			SDL_RenderCopyEx(m_render, Explosion_img.get(), &sRect, &FBSGroup[i].FireBallLocation, 0, nullptr, m_boss->flip);
			FBSGroup[i].updateIndex();
		}
		else
		{
			SDL_Rect sRect = { FireBall_move_vec[index] * 46, 0, 46,46 };
			SDL_RenderCopyEx(m_render, FireBall_move_img.get(), &sRect, &FBSGroup[i].FireBallLocation, FBSGroup[i].m_angle, nullptr, m_boss->flip);
		}
#ifdef SHOW_Rect
		SDL_SetRenderDrawColor(m_render, 0, 0, 255, 0xFF);
		SDL_RenderDrawRect(m_render, &FBSGroup[i].FireBallLocation);

		SDL_SetRenderDrawColor(m_render, 255, 255, 0, 0xFF);
		SDL_Rect sRect = { FBSGroup[i].FireBallLocation.x + 80, FBSGroup[i].FireBallLocation.y + 70, 55,55 };
		SDL_RenderDrawRect(m_render, &sRect);
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

void FireBall::checkExplosion()
{
	SDL_Rect r1{};
	m_scenes->getPillarRectCollision(r1);
	for (auto& it : FBSGroup)
	{
		if (it.boom)
		{
			continue;
		}
		SDL_Rect sRect = { it.FireBallLocation.x + 80,  it.FireBallLocation.y + 70, 55,55 };
		if (SDL_HasIntersection(&GroundCollision, &sRect))
		{
			it.boom = true;
			it.index = 0;
		}
		if (SDL_HasIntersection(&m_player->PlayerCollision, &sRect))
		{
			it.boom = true;
			it.index = 0;
			m_player->setHp(-10);
			m_ui->setPlayerHpValue(m_player->getHp());
			m_player->BeHit();
		}
		if (SDL_HasIntersection(&r1, &sRect))
		{
			it.boom = true;
			it.index = 0;
		}
	}
}

void FireBall::leftShiftFireBall(int offset)
{
	for (auto& it : FBSGroup)
	{
		it.FireBallLocation.x += 4 + offset;
	}
}

void FireBall::rightShiftFireBall(int offset)
{
	for (auto& it : FBSGroup)
	{
		it.FireBallLocation.x -= 4 + offset;
	}
}

void FireBall::addFireBall(int num)
{
	if (m_boss->flip)
	{
		for (int i{ 0 }; i < 7; i++)
		{
			FBSGroup.push_back({ { m_boss->bossLocation.x - 30, 430,200,200 } ,(i - 1) * 15 });
		}
	}
	else
	{
		for (int i{ 0 }; i < 7; i++)
		{
			FBSGroup.push_back({ { m_boss->bossLocation.x + 225, 430,200,200 } ,(i - 1) * -15 });
		}
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
	if (!getCanInput())
	{
		return;
	}
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
	if (m_boss->flip)
	{
		for (int i{ 0 }; i < FBSGroup.size(); i++)
		{
			if (FBSGroup[i].boom)
			{
				continue;
			}
			FBSGroup[i].FireBallLocation.x -= Speed;
			Point C = rotatePoint({ (double)FBSGroup[i].InitLocation.x,(double)FBSGroup[i].InitLocation.y }, { (double)FBSGroup[i].FireBallLocation.x,450 }, FBSGroup[i].m_angle);
			FBSGroup[i].FireBallLocation.y = C.y;
		}
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
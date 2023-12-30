#include "FirePillar.h"

#include <random>
#include <string>
#include <algorithm>

FirePillar::FirePillar(SDL_Renderer* render) :
	m_render(render),
	FirePillar_img(IMG_LoadTexture(m_render, "assets/Boss/Fire Pillar/hell-beast-burn.png"), TextureDeleter),
	FirePillar_explosion_img(IMG_LoadTexture(m_render, "assets/Boss/Fire Pillar/explosion-4.png"), TextureDeleter),
	FirePillar_move_img(IMG_LoadTexture(m_render, "assets/Boss/Fire Pillar/fire-ball.png"), TextureDeleter)
{
}

FirePillar::~FirePillar()
{
}

void FirePillar::Start()
{
	LifeTime = SDL_GetTicks() + 5000;
	FirePillarCd = 20;
	Speed = 10;

	std::vector<int> numbers;
	for (int i = 1; i <= 30; ++i)
	{
		numbers.push_back(i);
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(numbers.begin(), numbers.end(), g);
	numbers.resize(10);

	for (int i = 0; i < FBSGroup.size(); i++)
	{
		FBSGroup[i].state = FirePillar::FirePillarState::State::move;
		FBSGroup[i].Location.x = 60 * numbers[i];
		FBSGroup[i].Location.y = 0;
		FBSGroup[i].stop = false;
	}
}

void FirePillar::Render()
{
	if (LifeTime <= SDL_GetTicks())
	{
		return;
	}
	Move();
	for (int i = 0; i < FBSGroup.size(); i++)
	{
		if (FBSGroup[i].stop == true)
			return;
		if (FBSGroup[i].state == FirePillar::FirePillarState::State::move)
		{
			SDL_Rect rect2{ 19 * FirePillar_move_vec[FBSGroup[i].index],0,19,16 };
			SDL_RenderCopyEx(m_render, FirePillar_move_img.get(), &rect2, &FBSGroup[i].Location, 270, nullptr, flip);
			FBSGroup[i].updateIndex();
		}
		if (FBSGroup[i].state == FirePillar::FirePillarState::State::explosion)
		{
			SDL_Rect rect1{ 128 * FirePillar_explosion_vec[FBSGroup[i].index],0,128,128 };
			SDL_RenderCopyEx(m_render, FirePillar_explosion_img.get(), &rect1, &FBSGroup[i].Location, 0, nullptr, flip);
			FBSGroup[i].updateIndex();
		}
		if (FBSGroup[i].state == FirePillar::FirePillarState::State::pillar)
		{
			SDL_Rect rect1{ 74 * FirePillar_vec[FBSGroup[i].index],0,74,160 };
			SDL_RenderCopyEx(m_render, FirePillar_img.get(), &rect1, &FBSGroup[i].Location, 0, nullptr, flip);
			FBSGroup[i].updateIndex();
		}
	}
}

void FirePillar::Update(Scenes* s, Boss* boss)
{
	if (boss->getBossStart() != Boss::BossState::_FirePillar)
	{
		return;
	}
	if (LifeTime <= SDL_GetTicks())
	{
		s->setBlack();
		s->setPillarHide();
		Start();
	}
	if (boss->getBossStart() == Boss::_Death)
	{
		LifeTime = 0;
	}

}

void FirePillar::Move()
{
	for (auto& it : FBSGroup)
	{
		if (it.state == FirePillar::FirePillarState::State::move)
		{
			it.Location.y += Speed;
			it.Location.w = 128;
			it.Location.h = 128;
			it.vec_size = FirePillar_move_vec.size();
		}
		if (it.state == FirePillar::FirePillarState::State::move && it.Location.y >= 400)
		{
			it.state = FirePillar::FirePillarState::State::explosion;
			it.index = 0;
			it.Location.w = 200;
			it.Location.h = 200;
			it.vec_size = FirePillar_explosion_vec.size();
			it.maxDuration = 100;
			it.lifeTime = SDL_GetTicks() + 600;
		}
		if (it.state == FirePillar::FirePillarState::State::explosion && it.lifeTime <= SDL_GetTicks())
		{
			it.state = FirePillar::FirePillarState::State::pillar;
			it.index = 0;
			it.Location.w = 148;
			it.Location.h = 320;
			it.vec_size = FirePillar_vec.size();
			it.maxDuration = 200;
			it.lifeTime = SDL_GetTicks() + 600;
		}
		if (it.state == FirePillar::FirePillarState::State::pillar && it.lifeTime <= SDL_GetTicks())
		{
			it.index = 0;
			it.stop = true;
		}
	}
}
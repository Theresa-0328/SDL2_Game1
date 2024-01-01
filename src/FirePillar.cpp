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
	LifeTime = SDL_GetTicks() + 8000;
	FirePillarCd = 20;
	Speed = 10;
	addFirePillar();
	waves = 1;
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
		if (FBSGroup[i]->state == FirePillar::FirePillarState::State::move)
		{
			SDL_Rect rect2{ 19 * FirePillar_move_vec[FBSGroup[i]->index],0,19,16 };
			SDL_RenderCopyEx(m_render, FirePillar_move_img.get(), &rect2, &FBSGroup[i]->Location, 270, nullptr, flip);
		}
		if (FBSGroup[i]->state == FirePillar::FirePillarState::State::explosion)
		{
			SDL_Rect rect1{ 128 * FirePillar_explosion_vec[FBSGroup[i]->index],0,128,128 };
			SDL_RenderCopyEx(m_render, FirePillar_explosion_img.get(), &rect1, &FBSGroup[i]->Location, 0, nullptr, flip);
		}
		if (FBSGroup[i]->state == FirePillar::FirePillarState::State::pillar)
		{
			SDL_Rect rect1{ 74 * FirePillar_vec[FBSGroup[i]->index],0,74,160 };
			SDL_RenderCopyEx(m_render, FirePillar_img.get(), &rect1, &FBSGroup[i]->Location, 0, nullptr, flip);
		}
		FBSGroup[i]->updateIndex();
	}
}

void FirePillar::Update(Boss* boss)
{
	if (boss->getBossStart() == Boss::_Death)
	{
		LifeTime = 0;
		return;
	}
	if (boss->getBossStart() != Boss::BossState::_FirePillar)
	{
		return;
	}
	if (LifeTime <= SDL_GetTicks())
	{
		Start();
	}
	if (LifeTime - 2000 < SDL_GetTicks() && waves == 1)
	{
		addFirePillar();
		waves = 2;
	}
}

void FirePillar::Move()
{
	for (int i = 0; i < FBSGroup.size(); i++)
	{
		FirePillarState* Fp = FBSGroup[i];
		if (Fp->state == FirePillar::FirePillarState::State::move)
		{
			Fp->index = 0;
			Fp->Location.y += Speed;
			Fp->Location.w = 128;
			Fp->Location.h = 128;
			Fp->vec_size = FirePillar_move_vec.size();
		}
		if (Fp->state == FirePillar::FirePillarState::State::move && Fp->Location.y >= 400)
		{
			Fp->state = FirePillar::FirePillarState::State::explosion;
			Fp->index = 0;
			Fp->Location.w = 200;
			Fp->Location.h = 200;
			Fp->vec_size = FirePillar_explosion_vec.size();
			Fp->maxDuration = 100;
			Fp->lifeTime = SDL_GetTicks() + 600;
		}
		if (Fp->state == FirePillar::FirePillarState::State::explosion && Fp->lifeTime <= SDL_GetTicks())
		{
			Fp->state = FirePillar::FirePillarState::State::pillar;
			Fp->index = 0;
			Fp->Location.y = 0;
			Fp->Location.w = 300;
			Fp->Location.h = 640;
			Fp->vec_size = FirePillar_vec.size();
			Fp->maxDuration = 200;
			Fp->lifeTime = SDL_GetTicks() + 2000;
		}
		if (FBSGroup[i]->state == FirePillar::FirePillarState::State::pillar && FBSGroup[i]->lifeTime <= SDL_GetTicks())
		{
			std::swap(FBSGroup[i], FBSGroup.back());
			FBSGroup.pop_back();
			delete Fp;
		}
	}
}

void FirePillar::addFirePillar(int num)
{
	std::vector<int> numbers;
	for (int i = 1; i <= 30; ++i)
	{
		numbers.push_back(i);
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(numbers.begin(), numbers.end(), g);
	numbers.resize(num);
	for (int i = 0; i < num; i++)
	{
		SDL_Rect Location{ 70 * numbers[i] ,0,0,0 };
		FBSGroup.push_back(new FirePillarState(Location, FirePillar::FirePillarState::State::move));
	}
}

void FirePillar::setKeyboard(bool left, bool right)
{
	if (left)
	{
		leftShiftFirePillar();
	}
	if (right)
	{
		rightShiftFirePillar();
	}
}

void FirePillar::leftShiftFirePillar()
{
	for (auto& it : FBSGroup)
	{
		it->Location.x += 4;
	}
}

void FirePillar::rightShiftFirePillar()
{
	for (auto& it : FBSGroup)
	{
		it->Location.x -= 4;
	}
}

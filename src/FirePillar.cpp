#include "FirePillar.h"

#include <random>
#include <string>
#include <algorithm>

#include "Boss.h"
#include "Player.h"

FirePillar::FirePillar(SDL_Renderer* render) :
	m_render(render),
	FirePillar_img(IMG_LoadTexture(m_render, "assets/Boss/Fire Pillar/hell-beast-burn.png"), TextureDeleter),
	FirePillar_explosion_img(IMG_LoadTexture(m_render, "assets/Boss/Fire Pillar/explosion-4.png"), TextureDeleter),
	FirePillar_move_img(IMG_LoadTexture(m_render, "assets/Boss/Fire Pillar/fire-ball.png"), TextureDeleter),
	m_player(nullptr),
	m_ui(nullptr),
	m_audio(nullptr)
{
}

FirePillar::~FirePillar()
{
}

void FirePillar::Init(Boss* boss, Player* player, UI* ui, Audio* audio)
{
	m_boss = boss;
	m_player = player;
	m_ui = ui;
	m_audio = audio;
}

void FirePillar::Start()
{
	LifeTime = SDL_GetTicks() + 10000;
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
			SDL_RenderCopyEx(m_render, FirePillar_move_img.get(), &rect2, &FBSGroup[i]->Location, -90, nullptr, flip);
			FBSGroup[i]->Collision = { FBSGroup[i]->Location.x + 20,FBSGroup[i]->Location.y + 8, 60,107 };
		}
		if (FBSGroup[i]->state == FirePillar::FirePillarState::State::explosion)
		{
			SDL_Rect rect1{ 128 * FirePillar_explosion_vec[FBSGroup[i]->index],0,128,128 };
			SDL_RenderCopyEx(m_render, FirePillar_explosion_img.get(), &rect1, &FBSGroup[i]->Location, 0, nullptr, flip);
			FBSGroup[i]->Collision = { FBSGroup[i]->Location.x + 66,FBSGroup[i]->Location.y + 30, 245,398 };
		}
		if (FBSGroup[i]->state == FirePillar::FirePillarState::State::pillar)
		{
			SDL_Rect rect1{ 74 * FirePillar_vec[FBSGroup[i]->index],0,74,160 };
			SDL_RenderCopyEx(m_render, FirePillar_img.get(), &rect1, &FBSGroup[i]->Location, 0, nullptr, flip);
			FBSGroup[i]->Collision = { FBSGroup[i]->Location.x + 28,FBSGroup[i]->Location.y, 225,645 };
		}
#ifdef SHOW_Rect
		SDL_SetRenderDrawColor(m_render, 0, 0, 255, 0xFF);
		SDL_RenderDrawRect(m_render, &FBSGroup[i]->Location);

		SDL_SetRenderDrawColor(m_render, 255, 255, 0, 0xFF);
		SDL_RenderDrawRect(m_render, &FBSGroup[i]->Collision);
#endif
		FBSGroup[i]->updateIndex();
	}
}

void FirePillar::Update()
{
	if (m_boss->getBossStart() == Boss::_Death)
	{
		LifeTime = 0;
		return;
	}
	if (m_boss->getBossStart() != Boss::BossState::_FirePillar)
	{
		return;
	}
	if (LifeTime <= SDL_GetTicks())
	{
		Start();
	}
	if (LifeTime - 7500 < SDL_GetTicks() && waves == 1)
	{
		addFirePillar();
		waves = 2;
	}
	if (LifeTime - 5000 < SDL_GetTicks() && waves == 2)
	{
		addFirePillar();
		waves = 3;
	}
	if (LifeTime - 2500 < SDL_GetTicks() && waves == 3)
	{
		addFirePillar();
		waves = 4;
	}
	checkExplosion();
}

void FirePillar::Move()
{
	for (int i = 0; i < FBSGroup.size(); i++)
	{
		FirePillarState* Fp = FBSGroup[i];
		if (Fp->state == FirePillar::FirePillarState::State::move)
		{
			Fp->Location.y += Speed;
			Fp->Location.w = 107;
			Fp->Location.h = 128;
			Fp->vec_size = FirePillar_move_vec.size();
		}
		if (Fp->state == FirePillar::FirePillarState::State::move && Fp->Location.y >= 400)
		{
			Fp->state = FirePillar::FirePillarState::State::explosion;
			Fp->index = 0;
			Fp->Location.x -= 100;
			Fp->Location.y = 210;
			Fp->Location.w = 380;
			Fp->Location.h = 450;
			Fp->vec_size = FirePillar_explosion_vec.size();
			Fp->maxDuration = 100;
			Fp->lifeTime = SDL_GetTicks() + 600;
		}
		if (Fp->state == FirePillar::FirePillarState::State::explosion && Fp->lifeTime <= SDL_GetTicks())
		{
			m_audio->PlayGameSound("Fire1");
			Fp->state = FirePillar::FirePillarState::State::pillar;
			Fp->index = 0;
			Fp->Location.x += 40;
			Fp->Location.y = 0;
			Fp->Location.w = 300;
			Fp->Location.h = 650;
			Fp->vec_size = FirePillar_vec.size();
			Fp->maxDuration = 150;
			Fp->lifeTime = SDL_GetTicks() + 1200;
		}
		if (FBSGroup[i]->state == FirePillar::FirePillarState::State::pillar && FBSGroup[i]->lifeTime <= SDL_GetTicks())
		{
			std::swap(FBSGroup[i], FBSGroup.back());
			FBSGroup.pop_back();
			delete Fp;
		}
	}
}

void FirePillar::checkExplosion()
{
	for (int i = 0; i < FBSGroup.size(); i++)
	{
		if (SDL_HasIntersection(&FBSGroup[i]->Collision, &m_player->PlayerCollision))
		{
			if (m_player->getDefendState())
			{
				continue;
			}
			m_player->setHp(-10);
			m_ui->setPlayerHpValue(m_player->getHp());
			m_player->BeHit();
		}
	}
}

void FirePillar::addFirePillar(int num)
{
	std::vector<int> numbers;
	for (int i{ -15 }; i <= 15; ++i)
	{
		numbers.push_back(i);
	}
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(numbers.begin(), numbers.end(), g);
	numbers.resize(num);
	for (int i = 0; i < num; i++)
	{
		SDL_Rect Location{ 100 * numbers[i] ,0,0,0 };
		FBSGroup.push_back(new FirePillarState(Location, FirePillar::FirePillarState::State::move));
	}
	m_audio->PlayGameSound("Fire");
}

void FirePillar::setKeyboard(bool left, bool right)
{
	if (!getCanInput())
	{
		return;
	}
	if (left)
	{
		leftShiftFirePillar();
	}
	if (right)
	{
		rightShiftFirePillar();
	}
}

void FirePillar::leftShiftFirePillar(int offset)
{
	for (auto& it : FBSGroup)
	{
		it->Location.x += 4 + offset;
	}
}

void FirePillar::rightShiftFirePillar(int offset)
{
	for (auto& it : FBSGroup)
	{
		it->Location.x -= 4 + offset;
	}
}

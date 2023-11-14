#include "Boss.h"

Boss::Boss(SDL_Renderer* render)
	:m_render(render),
	Idle_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Idle.png"), TextureDeleter),
	Attack_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Attack.png"), TextureDeleter),
	Death_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Death.png"), TextureDeleter),
	Walk_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Walk.png"), TextureDeleter),
	Get_Hit_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Get Hit.png"), TextureDeleter)
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
	SDL_Rect sRect = { current[index].second * 90, current[index].first * 90, 90,90 };
	SDL_Rect dRect = { 0, 380, 360, 360 };
	SDL_RenderCopyEx(m_render, cur_ptr.get(), &sRect, &dRect, 0, nullptr, flip);

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

void Boss::getInfo()
{
	if (index != 0)
		return;
	if (a == 0)
	{
		UpdateBossState(_FireBall);
		a = 1;
		return;
	}
	if (a == 1)
	{
		UpdateBossState(_Dash);
		a = 0;
	}
}

void Boss::UpdateBossState(BossState state)
{
	switch (state)
	{
	case Boss::_FireBall:
		FireBallSkill();
		break;
	case Boss::_FirePillar:
		FirePillarSkill();
		break;
	case Boss::_Dash:
		DashSkill();
		break;
	case Boss::_Idle:
		IdleProccess();
		break;
	case Boss::_BeHit:
		BeHitProccess();
		break;
	case Boss::_Death:
		DeathProccess();
		break;
	default:
		break;
	}
}

void Boss::FireBallSkill()
{
	current = Attack;
	cur_ptr = Attack_img;
}

void Boss::IdleProccess()
{
	current = idle;
	cur_ptr = Idle_img;
}

void Boss::DeathProccess()
{
	current = Death;
	cur_ptr = Death_img;
}

void Boss::DashSkill()
{
	current = Walk;
	cur_ptr = Walk_img;
}

void Boss::BeHitProccess()
{
	current = Get_Hit;
	cur_ptr = Get_Hit_img;
}

void Boss::FirePillarSkill()
{

}

#include "Boss.h"

Boss::Boss(SDL_Renderer* render)
	:m_render(render),
	Idle_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Idle.png"), TextureDeleter),
	Attack_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Attack.png"), TextureDeleter),
	Death_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Death.png"), TextureDeleter),
	Walk_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Walk.png"), TextureDeleter),
	Get_Hit_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Get Hit.png"), TextureDeleter)
{
}

Boss::~Boss()
{
}

void Boss::Render()
{
	SDL_Rect sRect = { current[index] * 90, 0, 90,90 };
	SDL_Rect dRect = { 0, 380, 360, 360 };
	SDL_RenderCopyEx(m_render, cur_ptr.get(), &sRect, &dRect, 0, nullptr, flip);
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

void Boss::update()
{
	UpdateBossState(m_boss_state);
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
	if (FireBallAttackTime <= SDL_GetTicks())
	{
		DashSkillTime = static_cast<uint64_t>(5000) + SDL_GetTicks();
		m_boss_state = _Dash;
		index = 0;
	}
}

void Boss::IdleProccess()
{
	current = idle;
	cur_ptr = Idle_img;
	if (IdleTime <= SDL_GetTicks())
	{
		FireBallAttackTime = static_cast<uint64_t>(7200) + SDL_GetTicks();
		m_boss_state = _FireBall;
		index = 0;
	}
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
	if (DashSkillTime <= SDL_GetTicks())
	{
		FireBallAttackTime = static_cast<uint64_t>(7200) + SDL_GetTicks();
		m_boss_state = _FireBall;
		index = 0;
	}
}

void Boss::BeHitProccess()
{
	current = Get_Hit;
	cur_ptr = Get_Hit_img;
}

void Boss::FirePillarSkill()
{
	current = Attack;
	cur_ptr = Attack_img;
}

Boss::BossState Boss::getBossStart()
{
	return m_boss_state;
}

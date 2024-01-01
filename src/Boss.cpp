#include "Boss.h"

Boss::Boss(SDL_Renderer* render, Scenes* scenes)
	:m_render(render),
	Idle_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Idle.png"), TextureDeleter),
	Attack_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Attack.png"), TextureDeleter),
	Death_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Death.png"), TextureDeleter),
	Walk_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Walk.png"), TextureDeleter),
	Get_Hit_img(IMG_LoadTexture(m_render, "assets/Boss/Worm/Get Hit.png"), TextureDeleter),
	m_scenes(scenes)
{
}

Boss::~Boss()
{
}

void Boss::Render()
{
	SDL_Rect sRect = { current[index] * 90, 0, 90,90 };
	SDL_RenderCopyEx(m_render, cur_ptr.get(), &sRect, &bossLocation, 0, nullptr, flip);

#ifdef SHOW_Rect
	SDL_SetRenderDrawColor(m_render, 0, 0, 255, 0xFF);
	SDL_RenderDrawRect(m_render, &bossLocation);
#endif

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

void Boss::IdleProccess()
{
	current = idle;
	cur_ptr = Idle_img;
	if (IdleTime > SDL_GetTicks())
	{
		return;
	}
	if (FirePillarCd <= SDL_GetTicks())
	{
		m_boss_state = _FirePillar;
		FirePillarCd = SDL_GetTicks() + static_cast<uint64_t>(15000);
		FirePillarAttackTime = SDL_GetTicks() + static_cast<uint64_t>(8000);
		m_scenes->setSkyState(true);
		m_scenes->setPillarHide();
	}
	else
	{
		FireBallAttackTime = static_cast<uint64_t>(7200) + SDL_GetTicks();
		m_boss_state = _FireBall;
	}
	index = 0;
}

void Boss::FireBallSkill()
{
	current = Attack;
	cur_ptr = Attack_img;
	if (FireBallAttackTime > SDL_GetTicks())
	{
		return;
	}
	if (isDead)
	{
		m_boss_state = _Death;
	}
	else
	{
		IdleTime = static_cast<uint64_t>(4800) + SDL_GetTicks();
		m_boss_state = _Idle;
		index = 0;
	}
}

void Boss::FirePillarSkill()
{
	current = Attack;
	cur_ptr = Attack_img;
	if (FirePillarAttackTime > SDL_GetTicks())
	{
		return;
	}
	if (isDead)
	{
		m_boss_state = _Death;
	}
	else
	{
		IdleTime = static_cast<uint64_t>(4800) + SDL_GetTicks();
		m_boss_state = _Idle;
		index = 0;
	}
	m_scenes->setSkyState(false);
	m_scenes->setPillarHide();
}

void Boss::leftShiftBoss()
{
	bossLocation.x += 4;
}

void Boss::rightShiftBoss()
{
	bossLocation.x -= 4;
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

Boss::BossState Boss::getBossStart()
{
	return m_boss_state;
}

void Boss::setKeyboard(bool left, bool right)
{
	if (left)
	{
		leftShiftBoss();
	}
	if (right)
	{
		rightShiftBoss();
	}
}

#include "Player.h"

#include <iostream>

#include "Global.hpp"

Player::Player(SDL_Renderer* render)
	:m_render(render),
	player2(IMG_LoadTexture(render, "assets/player/player2.png"))
{
}

Player::~Player()
{
}

void Player::Render()
{
	if (!IsRender)
	{
		goto end;
	}
	if (human_index >= current.size())
	{
		human_index = 0;
	}
	{
		SDL_Rect sRect = { current[human_index].second * widthSpr, current[human_index].first * heightSpr, widthSpr, heightSpr };
		SDL_RenderCopyEx(m_render, player2, &sRect, &player2_img_rect, 0, nullptr, human_flip);
	}
end:
#ifdef SHOW_Rect
	SDL_SetRenderDrawColor(m_render, 0, 0, 255, 0xFF);
	SDL_RenderDrawRect(m_render, &player2_img_rect);

	SDL_SetRenderDrawColor(m_render, 255, 255, 0, 0xFF);
	SDL_RenderDrawRect(m_render, &PlayerCollision);

	SDL_Rect r1{};
	m_scenes->getPillarRectCollision(r1);
	SDL_Rect ground{ r1.x,r1.y,r1.w,5 };
	SDL_Rect player_bottom{ PlayerCollision.x,PlayerCollision.y + PlayerCollision.h - 1 ,PlayerCollision.w,5 };
	SDL_SetRenderDrawColor(m_render, 255, 0, 0, 0xFF);
	SDL_RenderDrawRect(m_render, &ground);
	SDL_RenderDrawRect(m_render, &player_bottom);
#endif // SHOW_Rect

	currentTime = SDL_GetTicks();
	if (currentTime > human_spriteChangeTime)
	{
		human_spriteChangeTime += human_maxDuration;
		human_index++;
		if (human_index >= current.size())
		{
			if (current == die)
			{
				human_index = 6;
				return;
			}
			human_index = 0;
		}
	}
}

void Player::Update()
{
	if (Hp <= 0)
	{
		isDead = true;
		SetAllCanInput(false);
		return;
	}
	InAttack();
	Defend();
	//CheckGround();
}

void Player::setKeyboard(bool left, bool right, bool J, bool Space1, bool Space2, bool K)
{
	if (isDead)
	{
		current = die;
		return;
	}
	if (IsHit)
	{
		return;
	}
	if (current != attack1 && current != attack2 && current != jump && current != fall && current != slide)
	{
		current = idle2;
		Move(left, right);
	}
	//Temp
	if (current != slide && Space1 && b1)
	{
		Jump();
		b1 = false;
	}
	else if (Space2)
	{
		b1 = true;
	}
	if (IsGround == true && J)
	{
		Attack();
	}
	else if (!J && canInput)
	{
		SetAllCanInput(true);
	}
	if (K)
	{
		StartSliding();
	}
}

void Player::Init(UI* ui, Scenes* s, Boss* b)
{
	m_scenes = s;
	m_boss = b;
	m_ui = ui;
}

void Player::setHp(int hp)
{
	Hp += hp;
	if (Hp <= 0)
	{
		Hp = 0;
	}
}

int Player::getHp() const
{
	return Hp;
}

void Player::Move(bool left, bool right)
{
	if (left)
	{
		current = run;
		human_flip = SDL_FLIP_HORIZONTAL;
	}
	else if (right)
	{
		current = run;
		human_flip = SDL_FLIP_NONE;
	}
}

Uint32 Player::jump1Callback(Uint32 interval, void* param)
{
	Player* it{ static_cast<Player*>(param) };
	it->player2_img_rect.y -= 4;
	it->PlayerCollision.y -= 4;
	if (it->PlayerCollision.y <= 400)
	{
		it->player2_img_rect.y += 1;
		it->PlayerCollision.y += 1;
	}
	if (it->human_index == 7)
	{
		it->myTimerID = SDL_AddTimer(100, Player::fallCallback, param);
		return 0;
	}
	else
	{
		return 16;
	}
}

Uint32 Player::fallCallback(Uint32 interval, void* param)
{
	Player* it{ static_cast<Player*>(param) };
	it->current = it->fall;
	it->player2_img_rect.y += 5;
	it->PlayerCollision.y += 5;
	SDL_Rect r1{};
	it->m_scenes->getPillarRectCollision(r1);
	if (it->PlayerCollision.y >= 400)
	{
		it->player2_img_rect.y += 1;
		it->PlayerCollision.y += 1;
	}
	if (it->PlayerCollision.y > 536)
	{
		it->current = it->idle2;
		it->IsGround = true;
		it->JumpCount = 0;
		return 0;
	}
	else if (it->isInPillar(r1))
	{
		it->current = it->idle2;
		it->IsGround = true;
		it->JumpCount = 0;
		it->myTimerID = SDL_AddTimer(100, Player::InPillarCallback, param);
		return 0;
	}
	else
	{
		return 16;
	}
}

Uint32 Player::jump2Callback(Uint32 interval, void* param)
{
	Player* it{ static_cast<Player*>(param) };
	it->player2_img_rect.y -= 4;
	it->PlayerCollision.y -= 4;
	if (it->PlayerCollision.y <= 400)
	{
		it->PlayerCollision.y += 1;
		it->player2_img_rect.y += 1;
	}
	if (it->human_index == 7)
	{
		SDL_AddTimer(100, Player::fallCallback, param);
		return 0;
	}
	else
	{
		return 16;
	}
}

Uint32 Player::InPillarCallback(Uint32 interval, void* param)
{
	Player* it{ static_cast<Player*>(param) };
	SDL_Rect r1{};
	it->m_scenes->getPillarRectCollision(r1);
	if (!it->isInPillar(r1))
	{
		SDL_AddTimer(100, Player::fallCallback, param);
		it->IsGround = false;
		return 0;
	}
	return 16;
}

Uint32 Player::Attack1Callback(Uint32 interval, void* param)
{
	Player* it{ static_cast<Player*>(param) };
	//std::cout << "Attack1 it->human_index " << it->human_index << "\n";
	it->checkAttackHit();
	if (it->human_index == 4)
	{
		it->canInput = true;
		it->current = it->idle2;
		return 0;
	}
	return 16;
}

Uint32 Player::Attack2Callback(Uint32 interval, void* param)
{
	Player* it{ static_cast<Player*>(param) };
	//std::cout << "Attack2 it->human_index " << it->human_index << "\n";
	it->checkAttackHit();
	if (it->human_index == 5)
	{
		it->canInput = true;
		it->current = it->idle2;
		return 0;
	}
	return 16;
}

void Player::CheckGround()
{
	if (player2_img_rect.y >= 515)
	{
		IsGround = true;
		IsJump = !IsGround;
	}
}

void Player::Jump()
{
	if (IsGround)
	{
		if (myTimerID != 0)
		{
			SDL_RemoveTimer(myTimerID);
			myTimerID = 0;
		}
		IsGround = false;
		IsJump = true;
		current = jump;
		human_index = 0;
		myTimerID = SDL_AddTimer(16, Player::jump1Callback, this);
		JumpCount++;
		JumpSpeed = 4;
	}
	else if (JumpCount > 0 && JumpCount < JumpMax)
	{
		if (myTimerID != 0)
		{
			SDL_RemoveTimer(myTimerID);
			myTimerID = 0;
		}
		current = jump;
		human_index = 0;
		JumpCount++;
		myTimerID = SDL_AddTimer(16, Player::jump2Callback, this);
	}
}

void Player::Attack()
{
	if (!canInput)
		return;
	SetAllCanInput(false);
	canInput = false;
	AttackMode = 1;
	ComboCount++;
	if (ComboCount > 2)
	{
		ComboCount = 1;
	}
	StartComboTime = SDL_GetTicks() + ComboTime;
	if (ComboCount == 1)
	{
		current = attack1;
		human_index = 0;
		HitBoss = false;
		SDL_AddTimer(16, Player::Attack1Callback, this);
	}
	if (ComboCount == 2)
	{
		current = attack2;
		human_index = 0;
		HitBoss = false;
		SDL_AddTimer(16, Player::Attack2Callback, this);
	}
}

bool Player::isInPillar(SDL_Rect rect1)
{
	SDL_Rect player_bottom{ PlayerCollision.x,PlayerCollision.y + PlayerCollision.h - 1 ,PlayerCollision.w,5 };
	SDL_Rect ground{ rect1.x,rect1.y,rect1.w,5 };
	if (SDL_HasIntersection(&player_bottom, &ground))
	{
		player_bottom.y = 430;
		return true;
	}
	return false;
}

void Player::InAttack()
{
	if (StartComboTime < SDL_GetTicks())
	{
		StartComboTime = 0;
		ComboCount = 0;
	}
}

void Player::SetAllCanInput(bool CanInput)
{
	m_scenes->setCanInput(CanInput);
	m_boss->setCanInput(CanInput);
	m_boss->setFireCanInput(CanInput);
}

void Player::checkAttackHit()
{
	if (HitBoss)
		return;
	SDL_Rect Rect = { m_boss->bossLocation.x + 89, m_boss->bossLocation.y + 132, 221,127 };
	if (!SDL_HasIntersection(&PlayerCollision, &Rect))
	{
		return;
	}
	HitBoss = true;
	if (AttackMode == 1)
	{
		m_boss->setHp(-10);
		m_ui->setBossHpValue(m_boss->getHp());
	}
}

void Player::StartSliding()
{
	if (IsSliding || SlidTime > SDL_GetTicks())
	{
		std::cout << "Remaining cooldown time for Slide Tackle skill : " << SlidTime - SDL_GetTicks() << std::endl;
		return;
	}
	SlidTime = SDL_GetTicks() + SlidCd;
	current = slide;
	IsSliding = true;
	human_index = 0;
	SetAllCanInput(false);
	if (!human_flip)
	{
		movefunction = [&](int i)
			{
				m_scenes->rightShiftScene(i);
				m_boss->rightShiftBoss(i);
				m_boss->rightShiftskill(i);
			};
	}
	else
	{
		movefunction = [&](int i)
			{
				m_scenes->leftShiftScene(i);
				m_boss->leftShiftBoss(i);
				m_boss->leftShiftskill(i);
			};
	}
	SDL_AddTimer(16, Player::SlidCallback, this);
}

Uint32 Player::SlidCallback(Uint32 interval, void* param)
{
	Player* it{ static_cast<Player*>(param) };
	if (it->human_index == 4)
	{
		it->canInput = true;
		it->IsSliding = false;
		it->current = it->idle2;
		it->SetAllCanInput(true);
		return 0;
	}
	it->movefunction(6);
	return 16;
}

Uint32 Player::BeHitCallback(Uint32 interval, void* param)
{
	Player* it{ static_cast<Player*>(param) };
	it->IsHit = false;
	it->current = it->idle2;
	it->human_maxDuration = 150;
	it->StartDefendTime = SDL_GetTicks() + it->DefendTime;
	it->FlashTep = SDL_GetTicks() + it->FlashingTime;
	it->SetAllCanInput(true);
	return 0;
}

Uint32 Player::RepelCallback(Uint32 interval, void* param)
{
	thread_local int i{ 0 };
	Player* it{ static_cast<Player*>(param) };
	if (i > 10)
	{
		i = 0;
		return 0;
	}
	i++;
	it->movefunction(1);
	return 16;
}

void Player::BeHit()
{
	IsHit = true;
	current = hurt;
	IsDefend = true;
	SetAllCanInput(false);
	human_maxDuration = 300;
	if (!m_boss->flip)
	{
		movefunction = [&](int i)
			{
				m_scenes->rightShiftScene(i);
				m_boss->rightShiftBoss(i);
				m_boss->rightShiftskill(i);
			};
	}
	else
	{
		movefunction = [&](int i)
			{
				m_scenes->leftShiftScene(i);
				m_boss->leftShiftBoss(i);
				m_boss->leftShiftskill(i);
			};
	}
	SDL_AddTimer(16, Player::RepelCallback, this);
	SDL_AddTimer(800, Player::BeHitCallback, this);
}

bool Player::getDefendState() const
{
	return IsDefend;
}

void Player::Defend()
{
	if (!IsDefend || IsHit)
	{
		return;
	}
	if (StartDefendTime > SDL_GetTicks())
	{
		if (FlashTep > SDL_GetTicks())
		{
			return;
		}
		if (IsDisplay)
		{
			IsRender = false;
			IsDisplay = false;
		}
		else
		{
			IsRender = true;
			IsDisplay = true;
		}
		FlashTep = SDL_GetTicks() + FlashingTime;
	}
	else
	{
		IsDefend = false;
		IsDisplay = true;
		IsRender = true;
	}
}

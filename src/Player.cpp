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
	if (human_index >= current.size())
	{
		human_index = 0;
	}

	SDL_Rect sRect = { current[human_index].second * widthSpr, current[human_index].first * heightSpr, widthSpr, heightSpr };
	SDL_RenderCopyEx(m_render, player2, &sRect, &player2_img_rect, 0, nullptr, human_flip);

	currentTime = SDL_GetTicks();
	if (currentTime > human_spriteChangeTime)
	{
		human_spriteChangeTime += human_maxDuration;
		human_index++;
		if (human_index >= current.size())
		{
			human_index = 0;
		}
	}

#ifdef SHOW_Rect
	SDL_SetRenderDrawColor(m_render, 0, 0, 255, 0xFF);
	SDL_RenderDrawRect(m_render, &player2_img_rect);

	SDL_SetRenderDrawColor(m_render, 255, 255, 0, 0xFF);
	SDL_RenderDrawRect(m_render, &PlayerCollision);
#endif // SHOW_Rect

}

void Player::Update()
{
	//CheckGround();
}

void Player::setKeyboard(bool left, bool right, bool J, bool Space1, bool Space2)
{
	if (current != jump && current != fall)
	{
		current = idle2;
		Move(left, right);
	}
	if (Space1 && b1)
	{
		Jump();
		b1 = false;
	}
	else if (Space2)
	{
		b1 = true;
	}
	if (J)
	{
		current = attack1;
	}
}

void Player::Init(Scenes* s)
{
	m_scenes = s;
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
	else if (it->isInPillar(it->PlayerCollision, r1))
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
	if (!it->isInPillar(it->PlayerCollision, r1))
	{
		SDL_AddTimer(100, Player::fallCallback, param);
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

bool Player::isInPillar(SDL_Rect rect1, SDL_Rect rect2)
{
	int topOfRect1 = rect1.y;
	int bottomOfRect1 = rect1.y + rect1.h;
	int topOfRect2 = rect2.y;
	int bottomOfRect2 = rect2.y + rect2.h;
	// 判断y轴是否相交
	bool isYIntersect = (topOfRect1 >= topOfRect2 && topOfRect1 <= bottomOfRect2) ||
		(bottomOfRect1 >= topOfRect2 && bottomOfRect1 <= bottomOfRect2);
	// 判断x轴是否相交
	bool isXIntersect = (rect1.x >= rect2.x && rect1.x <= rect2.x + rect2.w) ||
		(rect1.x + rect1.w >= rect2.x && rect1.x + rect1.w <= rect2.x + rect2.w);
	return isYIntersect && isXIntersect;
}

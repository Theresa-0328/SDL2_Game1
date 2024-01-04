#include "Ui.h"

UI::UI(SDL_Renderer* render) :
	m_render(render),
	rpg1(IMG_LoadTexture(m_render, "assets/Ui/rpg1.png")),
	rpg2(IMG_LoadTexture(m_render, "assets/Ui/rpg2.png")),
	rpg3(IMG_LoadTexture(m_render, "assets/Ui/rpg3.png"))
{
}

UI::~UI()
{
	SDL_DestroyTexture(rpg1);
	SDL_DestroyTexture(rpg2);
	SDL_DestroyTexture(rpg3);
}

void UI::Update()
{
}

void UI::Render()
{
	SDL_Rect Rect1{ 32, 40, 80 * 4,9 * 4 };
	SDL_RenderCopyEx(m_render, rpg2, &Player2Hp_img, &Rect1, 0, nullptr, SDL_FLIP_NONE);
	SDL_Rect Rect2{ 361, 645, 558,63 };
	SDL_RenderCopyEx(m_render, rpg2, &Player2Hp_img, &Rect2, 0, nullptr, SDL_FLIP_NONE);

	SDL_Rect Rect3{ 64, 48, PlayHp_img_w,20 };
	SDL_RenderCopyEx(m_render, rpg3, &Health_img, &Rect3, 0, nullptr, SDL_FLIP_NONE);
	SDL_Rect Rect4{ 417, 659, BossHp_img_w,36 };
	SDL_RenderCopyEx(m_render, rpg3, &Health_img, &Rect4, 0, nullptr, SDL_FLIP_NONE);
}

void UI::setPlayerHpValue(int value, int min1, int max1, int min2, int max2)
{
	PlayHp_img_w = static_cast<int>((value - min1) * (max2 - min2) / (max1 - min1) + min2);
}

void UI::setBossHpValue(int value, int min1, int max1, int min2, int max2)
{
	BossHp_img_w = static_cast<int>((value - min1) * (max2 - min2) / (max1 - min1) + min2);
}

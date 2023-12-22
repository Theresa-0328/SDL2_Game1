#include "FirePillar.h"

#include <random>

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
	LifeTime = SDL_GetTicks();
	FirePillarCd = 20;
	std::random_device rd;
	std::mt19937 gen(rd());
	int lower_bound = 1;
	int upper_bound = 10;
	std::uniform_int_distribution<int> distribution(lower_bound, upper_bound);
	for (int i = 0; i < 5; i++)
	{
		int r = distribution(gen);
	}
}

void FirePillar::Render()
{
	int index{ 0 };

	for (int i = 0; i < 5; i++)
	{
		int r{ 0 };
	}
	Move();
	SDL_Rect rect3{ 74 * 4,0,74,160 };
	SDL_Rect rect13{ 0,0,148,320 };
	SDL_RenderCopyEx(m_render, FirePillar_img.get(), &rect3, &rect13, 0, nullptr, flip);

	SDL_Rect rect1{ 128 * 5,0,128,128 };
	SDL_Rect rect11{ 200,0,128,128 };
	SDL_RenderCopyEx(m_render, FirePillar_explosion_img.get(), &rect1, &rect11, 0, nullptr, flip);

	SDL_Rect rect2{ 19 * 2,0,19,16 };
	SDL_Rect rect12{ 400,0,128,128 };
	SDL_RenderCopyEx(m_render, FirePillar_move_img.get(), &rect2, &rect12, 0, nullptr, flip);
}

void FirePillar::Update(Scenes* s)
{
	s->setBlack();
	s->setPillarHide();
}

void FirePillar::Move()
{

}

#include "FirePillar.h"

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
}

void FirePillar::Render()
{
	SDL_RenderCopyEx(m_render, FirePillar_img.get(), 0, 0, 0, nullptr, flip);
}

void FirePillar::Update()
{
}
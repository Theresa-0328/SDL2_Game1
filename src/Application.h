#pragma once

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include <Windows.h>
#include <stdlib.h>
#include <crtdbg.h>

#include "Player.h"
#include "Boss.h"
#include "FireBall.h"
#include "FirePillar.h"

class Application
{
public:
	Application();
	~Application();
	void run();
	bool ProcessMessage();
private:
	void init();
	void update();
	void render();
	int gWINDOW_WEIGHT;
	int gWINDOW_HEIGHT;
	SDL_Window* m_screen;
	SDL_Renderer* m_render;
	int renderW;
	int renderH;
	bool quit;
	uint32_t gFPS{ 60 };
	uint32_t gFPS_TIME{ 1000 / gFPS };
	SDL_Event event{};

	std::unique_ptr<Scenes> m_scenes;
	std::unique_ptr<Player> m_player;
	std::unique_ptr<Boss> m_boss;
	std::unique_ptr<FireBall> m_fireball;
	std::unique_ptr<FirePillar> m_firepillar;

	bool k_left{};
	bool k_right{};
	bool k_J{};
};
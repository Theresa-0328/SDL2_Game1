#pragma once

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include <Windows.h>
#include <stdlib.h>
#include <crtdbg.h>

#include "Scenes.h"

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
	bool k_left{};
	bool k_right{};
};
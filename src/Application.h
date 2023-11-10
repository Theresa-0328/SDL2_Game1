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
	int gWINDOW_WEIGHT;
	int gWINDOW_HEIGHT;
	SDL_Window* screen;
	SDL_Renderer* render;
	int renderW;
	int renderH;
	bool quit;
	SDL_Texture* texture;
	uint32_t gFPS{ 60 };
	uint32_t gFPS_TIME{ 1000 / gFPS };
	SDL_Event event{};
	int tigerHeadx{ -450 };
	int tigerHeady{ -150 };
};
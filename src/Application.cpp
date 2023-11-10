#include "Application.h"


Application::Application()
	:gWINDOW_WEIGHT(1280),
	gWINDOW_HEIGHT(720),
	screen(nullptr),
	render(nullptr),
	renderW(0),
	renderH(0),
	quit(false),
	texture(nullptr)
{
	int ret = SDL_Init(SDL_INIT_VIDEO);
	ret = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	if (ret != (IMG_INIT_PNG | IMG_INIT_JPG))
	{
		throw std::runtime_error("type_error");
	}
	screen = SDL_CreateWindow("SDL2_Game1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		gWINDOW_WEIGHT, gWINDOW_HEIGHT, NULL);
	render = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	SDL_GetRendererOutputSize(render, &renderW, &renderH);
}

Application::~Application()
{
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(screen);
	SDL_Quit();
}

void Application::run()
{
	int imgW{ 0 };
	int imgH{ 0 };
	// 由 surface 转换成 texture
	SDL_Texture* texture = IMG_LoadTexture(render, "assets/scenes/background.png");
	SDL_QueryTexture(texture, nullptr, nullptr, &imgW, &imgH);

	while (!quit)
	{
		std::chrono::time_point start = std::chrono::high_resolution_clock::now();

		SDL_SetRenderDrawColor(render, 135, 206, 0, 0xFF);
		SDL_RenderClear(render);

		Uint32 startMs = SDL_GetTicks();
		SDL_Rect sRect{ 0, 0, imgW, imgH, };
		SDL_Rect dRect{ tigerHeadx, -195, renderW * 1.7, renderH * 1.7 };
		SDL_RenderCopy(render, texture, &sRect, &dRect);

		SDL_Rect s1Rect{ 300, 50, 400, 500 }; // tigerhead img
		SDL_Rect d1Rect{ -160, tigerHeady, 400, 500 };
		//SDL_RenderCopy(render, texture, &s1Rect, &d1Rect);

		SDL_RenderPresent(render);
		Uint32 endMs = SDL_GetTicks();
		Uint32 consumeTime = endMs - startMs;
		SDL_Delay(consumeTime >= gFPS_TIME ? 0 : (gFPS_TIME - consumeTime)); // 调整帧率
		std::chrono::time_point end = std::chrono::high_resolution_clock::now();
		//std::cout << "FPS:" << std::chrono::seconds(1) / (end - start) << std::endl;
	}
}

bool Application::ProcessMessage()
{
	SDL_WaitEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
	{
		quit = true;
		return false;
	}
	case SDL_KEYDOWN:
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:  tigerHeadx -= 1; break;
		case SDLK_RIGHT: tigerHeadx += 1; break;
		case SDLK_UP:    tigerHeady -= 1; break;
		case SDLK_DOWN:  tigerHeady += 1; break;

		case SDLK_a: tigerHeadx -= 1; break;
		case SDLK_d: tigerHeadx += 1; break;
		case SDLK_w: tigerHeady -= 1; break;
		case SDLK_s: tigerHeady += 1; break;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
	return true;
}

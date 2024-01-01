#include "Application.h"


Application::Application() :
	gWINDOW_WEIGHT(1280),
	gWINDOW_HEIGHT(720),
	m_screen(nullptr),
	m_render(nullptr),
	renderW(0),
	renderH(0),
	quit(false),
	m_scenes(nullptr)
{
	int ret = SDL_Init(SDL_INIT_VIDEO);
	ret = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	if (ret != (IMG_INIT_PNG | IMG_INIT_JPG))
	{
		throw std::runtime_error("type_error");
	}
	m_screen = SDL_CreateWindow("SDL2_Game1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gWINDOW_WEIGHT, gWINDOW_HEIGHT, NULL);
	m_render = SDL_CreateRenderer(m_screen, -1, SDL_RENDERER_ACCELERATED);
	SDL_GetRendererOutputSize(m_render, &renderW, &renderH);
	m_scenes = std::make_unique<Scenes>(m_render);
	m_player = std::make_unique<Player>(m_render);
	m_boss = std::make_unique<Boss>(m_render, m_scenes.get());
	m_fireball = std::make_unique<FireBall>(m_render);
	m_firepillar = std::make_unique<FirePillar>(m_render);
}

Application::~Application()
{
	SDL_DestroyRenderer(m_render);
	SDL_DestroyWindow(m_screen);
	SDL_Quit();
}

void Application::run()
{
	init();
	while (!quit)
	{
		std::chrono::time_point start = std::chrono::high_resolution_clock::now();

		update();
		render();

		std::chrono::time_point end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		int delayTime = gFPS_TIME - static_cast<int>(duration);
		std::this_thread::sleep_for(std::chrono::milliseconds(delayTime >= 0 ? delayTime : 0));
		end = std::chrono::high_resolution_clock::now();
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
		case SDLK_LEFT:
		{
			k_left = true;
			break;
		}
		case SDLK_RIGHT:
		{
			k_right = true;
			break;
		}
		case SDLK_UP:   /* tigerHeady -= 1; */break;
		case SDLK_DOWN:  /*tigerHeady += 1;*/ break;

		case SDLK_a: k_left = true; break;
		case SDLK_d: k_right = true;  break;
		case SDLK_w: /*tigerHeady -= 1;*/ break;
		case SDLK_s: /*tigerHeady += 1;*/ break;
		case SDLK_j: k_J = true; break;
		default:
			break;
		}
		break;
	}
	case SDL_KEYUP:
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
		{
			k_left = false;
			break;
		}
		case SDLK_RIGHT:
		{
			k_right = false;
			break;
		}
		case SDLK_UP:   /* tigerHeady -= 1; */break;
		case SDLK_DOWN:  /*tigerHeady += 1;*/ break;

		case SDLK_a: k_left = false; break;
		case SDLK_d: k_right = false; break;
		case SDLK_w: /*tigerHeady -= 1;*/ break;
		case SDLK_s: /*tigerHeady += 1;*/ break;
		case SDLK_j: k_J = false; break;
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

void Application::init()
{
	m_fireball->Init(m_boss.get());
}

void Application::update()
{
	m_scenes->setKeyboard(k_left, k_right);
	m_player->setKeyboard(k_left, k_right, k_J);
	m_boss->setKeyboard(k_left, k_right);
	m_fireball->setKeyboard(k_left, k_right);

	m_boss->update();
	m_fireball->Update();
	m_firepillar->Update(m_boss.get());
}
int a = 0;
void Application::render()
{
	SDL_SetRenderDrawColor(m_render, 135, 206, 0, 0xFF);
	SDL_RenderClear(m_render);

	m_scenes->RenderBackground();
	m_boss->Render();
	m_player->task();
	m_scenes->RenderForeground();
	m_fireball->Render();
	m_firepillar->Render();

	SDL_RenderPresent(m_render);

	//SDL_Texture* texture = SDL_CreateTexture(
	//	m_render,
	//	SDL_PIXELFORMAT_ARGB8888,  // 根据需要使用适当的格式
	//	SDL_TEXTUREACCESS_TARGET,
	//	gWINDOW_WEIGHT,
	//	gWINDOW_HEIGHT
	//);
	//SDL_SetRenderTarget(m_render, texture);

	//SDL_RenderPresent(m_render);

	//SDL_SetRenderTarget(m_render, NULL);

	//SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, 1280, 720, 32, SDL_PIXELFORMAT_ARGB8888);

	//// 将纹理复制到 surface
	//SDL_RenderReadPixels(
	//	m_render,
	//	NULL,
	//	SDL_PIXELFORMAT_ARGB8888,
	//	surface->pixels,
	//	surface->pitch
	//);
	//a++;
	//std::string str = std::to_string(a) + "output.png";
	//IMG_SavePNG(surface, str.c_str());
}

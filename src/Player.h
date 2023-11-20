#pragma once
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

class Player
{
public:
	Player(SDL_Renderer* render);
	~Player();
	void task();
	void setKeyboard(bool left, bool right, bool J);
private:
	SDL_Renderer* m_render;

	SDL_Texture* player2;
	int player2_x{ 640 - 75 };
	int player2_y{ 520 };
	int widthSpr = 50;
	int heightSpr = 37;
	int imgW = widthSpr * 3;
	int imgH = heightSpr * 3;

	int human_index = 0;
	int human_maxDuration = 150;
	int human_currentTime = SDL_GetTicks();
	int currentTime = SDL_GetTicks();
	int human_spriteChangeTime = human_currentTime + human_maxDuration;

	SDL_RendererFlip human_flip = SDL_FLIP_NONE;

	std::vector<std::pair<int, int>> idle1{ {0, 0}, {0, 1}, {0, 2}, {0, 3} };
	std::vector<std::pair<int, int>> crouch{ {0, 4}, {0, 5}, {0, 6}, {1, 0} };
	std::vector<std::pair<int, int>> run{ {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6} };
	std::vector<std::pair<int, int>> jump{ {2, 0}, {2, 1}, {2, 2}, {2, 3} };
	std::vector<std::pair<int, int>> mid{ {2, 4}, {2, 5}, {2, 6}, {3, 0} };
	std::vector<std::pair<int, int>> fall{ {3, 1}, {3, 2} };
	std::vector<std::pair<int, int>> slide{ {3, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 0} };
	std::vector<std::pair<int, int>> grab{ {4, 1}, {4, 2}, {4, 3}, {4, 4} };
	std::vector<std::pair<int, int>> climb{ {4, 5}, {4, 6}, {5, 0}, {5, 1}, {5, 2} };
	std::vector<std::pair<int, int>> idle2{ {5, 3}, {5, 4}, {5, 5}, {5, 6} };
	std::vector<std::pair<int, int>> attack1{ {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4} };
	std::vector<std::pair<int, int>> attack2{ {6, 5}, {6, 6}, {7, 0}, {7, 1}, {7, 2}, {7, 3} };
	std::vector<std::pair<int, int>> attack3{ {7, 4}, {7, 5}, {7, 6}, {8, 0}, {8, 1}, {8, 2} };
	std::vector<std::pair<int, int>> hurt{ {8, 3}, {8, 4}, {8, 5} };
	std::vector<std::pair<int, int>> die{ {8, 6}, {9, 0}, {9, 1}, {9, 2}, {9, 3}, {9, 4}, {9, 5} };
	std::vector<std::pair<int, int>> jump2{ {9, 6}, {10, 0}, {10, 1} };
	std::vector<std::pair<int, int>> current = idle1;
};
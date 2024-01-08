#pragma once
#include <vector>
#include <functional>

#include <SDL.h>
#include <SDL_image.h>

#include "Audio.h"
#include "Boss.h"
#include "Scenes.h"

class Player
{
public:
	Player(SDL_Renderer* render);
	~Player();
	void Render();
	void Update();
	void setKeyboard(bool left, bool right, bool J, bool Space1, bool Space2, bool K);
	void Init(UI* ui, Scenes* s, Boss* b, Audio* audio);
	void setHp(int hp);
	int getHp() const;
	void BeHit();
	SDL_Rect PlayerCollision{ 606, 536, 58, 87 };
	bool getDefendState() const;
private:
	SDL_Renderer* m_render;
	Scenes* m_scenes{};
	Boss* m_boss{};
	UI* m_ui{};
	Audio* m_audio{};
	SDL_Texture* player2;

	int player2_x{ 565 };
	int player2_y{ 515 };
	int widthSpr = 50;
	int heightSpr = 37;
	int imgW = widthSpr * 3;
	int imgH = heightSpr * 3;
	SDL_Rect player2_img_rect{ player2_x, player2_y, imgW, imgH };

	int human_index = 0;
	int human_maxDuration = 100;
	int human_currentTime = SDL_GetTicks();
	int currentTime = SDL_GetTicks();
	int human_spriteChangeTime = human_currentTime + human_maxDuration;

	SDL_RendererFlip human_flip = SDL_FLIP_NONE;
	std::vector<std::pair<int, int>> idle1{ {0, 0}, {0, 1}, {0, 2}, {0, 3} };
	std::vector<std::pair<int, int>> crouch{ {0, 4}, {0, 5}, {0, 6}, {1, 0} };
	std::vector<std::pair<int, int>> run{ {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6} };
	//std::vector<std::pair<int, int>> jump{ {2, 0}, {2, 1}, {2, 2}, {2, 3} };
	std::vector<std::pair<int, int>> jump{ {2, 0}, {2, 1}, {2, 2}, {2, 3},{2, 4}, {2, 5}, {2, 6} ,{3, 0} };
	std::vector<std::pair<int, int>> mid{ {2, 4}, {2, 5}, {2, 6}, {3, 0} };
	std::vector<std::pair<int, int>> fall{ {3, 1}, {3, 2} };
	std::vector<std::pair<int, int>> slide{ {3, 3}, {3, 4}, {3, 5}, {3, 6}, {4, 0} };
	std::vector<std::pair<int, int>> grab{ {4, 1}, {4, 2}, {4, 3}, {4, 4} };
	std::vector<std::pair<int, int>> climb{ {4, 5}, {4, 6}, {5, 0}, {5, 1}, {5, 2} };
	std::vector<std::pair<int, int>> idle2{ {5, 3}, {5, 4}, {5, 5}, {5, 6} };
	std::vector<std::pair<int, int>> attack1{ {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4} };
	std::vector<std::pair<int, int>> attack2{ {6, 5}, {6, 6}, {7, 0}, {7, 1}, {7, 2}, {7, 3} };
	std::vector<std::pair<int, int>> attack3{ {7, 4}, {7, 5}, {7, 6}, {8, 0}, {8, 1}, {8, 2} };
	//std::vector<std::pair<int, int>> attack4{ {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4},{6, 5}, {6, 6}, {7, 0}, {7, 1}, {7, 2}, {7, 3} };
	std::vector<std::pair<int, int>> hurt{ {8, 3}, {8, 4}, {8, 5} };
	std::vector<std::pair<int, int>> die{ {8, 6}, {9, 0}, {9, 1}, {9, 2}, {9, 3}, {9, 4}, {9, 5} };
	std::vector<std::pair<int, int>> jump2{ {9, 6}, {10, 0}, {10, 1} };
	std::vector<std::pair<int, int>> current = idle2;

	bool b1{ true };
	Uint32 static jump1Callback(Uint32 interval, void* param);
	Uint32 static jump2Callback(Uint32 interval, void* param);
	Uint32 static Attack1Callback(Uint32 interval, void* param);
	Uint32 static Attack2Callback(Uint32 interval, void* param);
	Uint32 static SlidCallback(Uint32 interval, void* param);
	Uint32 static BeHitCallback(Uint32 interval, void* param);
	Uint32 static RepelCallback(Uint32 interval, void* param);
	SDL_TimerID myTimerID = 0;

	bool IsRender{ true };// 是否渲染玩家角色
	bool IsGround{ true };//判断能否跳跃
	bool IsJump{ false };//判断是否在空中
	static const int JumpMax{ 2 };//最大跳跃数
	int JumpCount{ 0 };//当前跳跃数
	int JumpSpeed{ 0 };//跳跃速度
	bool isDead{ false };//是否死亡
	bool canInput{ true };//是否可以输入
	int AttackMode{};//当前的攻击模式
	int ComboCount{};//连击计数
	uint32_t StartComboTime{};//开始连击时间
	uint32_t ComboTime{ 900 };//连击时间
	int MAX_HP{ 100 };//最大血量
	int Hp{ 100 };//当前血量
	bool HitBoss{ false };
	bool IsSliding{ false };
	uint32_t SlidTime{};//冲刺时间
	uint32_t SlidCountTime{};//冲刺计时器
	uint32_t SlidCd{ 3000 };//冲刺Cd
	bool IsHit{ false };//是否处于被攻击状态
	bool IsDefend{ false };//是否处于无敌状态
	bool IsDisplay{ true };//闪烁中的开关
	uint32_t StartDefendTime{};//开始无敌时间
	uint32_t DefendTime{ 2500 };//无敌时间
	uint32_t FlashTep{};//闪烁计时器
	uint32_t FlashingTime{ 300 };//闪烁间隔
	uint32_t FallTime{ 300 };//下落时间

	std::function<void(int)> movefunction{};

	void Run(bool left, bool right);
	void Jump();
	void Attack();
	bool isInPillar(SDL_Rect rect1);
	void InAttack();
	void SetAllCanInput(bool CanInput);
	void checkAttackHit();
	void StartSliding();
	void Defend();//无敌状态
	void CheckGround();
};
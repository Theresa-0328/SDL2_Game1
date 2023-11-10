﻿#include "Application.h"

#define _CRTDBG_MAP_ALLOC

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

	std::cout << "Hello SDL" << std::endl;

	Application app{};
	std::thread render{ [&]() {app.run(); } };
	while (app.ProcessMessage()) {}
	render.join();
	return 0;
}
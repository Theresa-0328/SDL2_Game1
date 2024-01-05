#include "Application.h"

#ifdef _WIN32
#define _CRTDBG_MAP_ALLOC
#endif // WIN32

int main(int argc, char* argv[])
{
#ifdef _WIN32
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
#endif // WIN32

	std::cout << "Hello SDL" << std::endl;

	Application app{};
	std::thread render{ [&]() {app.run(); } };
	while (app.ProcessMessage()) {}
	render.join();
	return 0;
}
#define _CRTDBG_MAP_ALLOC
#include "Game.h"
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

using namespace std;

const int width = 1080;
const int height = 720;
const int FPS = 60;
const int FrameDelay = 1000 / 60;
Game* game = nullptr;

int main(int argv, char* argc[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	game = new Game();

	Uint32 FrameStart;
	int FrameTime;

	game->init("Aerosmith", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, false);

	while (game->running())
	{
		FrameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		FrameTime = SDL_GetTicks() - FrameStart;
		if (FrameTime < FrameDelay)
		{
			SDL_Delay(FrameDelay - FrameTime);
		}
	}
	game->clean();
	delete game;
	game = nullptr;

	_CrtDumpMemoryLeaks();
	return 0;
}
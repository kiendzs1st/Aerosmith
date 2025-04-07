#include "Game.h"

using namespace std;

const int width = 1080;
const int height = 720;
const int FPS = 60;
const int FrameDelay = 1000 / 60;
Game* game = nullptr;

enum GameState
{
	State_Menu,
	State_Playing,
	State_End,
	State_Quit,
};

int main(int argv, char* argc[])
{

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
	return 0;
}
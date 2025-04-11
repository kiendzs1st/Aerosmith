#pragma once
#include <SDL.h>
#include "TextureManagement.h"
#include "StartMenu.h"
#include "ButtonStore.h"
#include "Font.h"

class GameOver
{
public: 
	GameOver(SDL_Renderer* ren, int score, int highscore);
	~GameOver();

	void Event(SDL_Event& event);
	MenuResult Update();
	void Render();

private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	MainButton* mainmenu;
	RestartButton* restart;
};

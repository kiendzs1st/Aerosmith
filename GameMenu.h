#pragma once
#include <SDL.h>
#include "ButtonStore.h"
#include "TextureManagement.h"
#include "StartMenu.h"
#include "XButton.h"

class GameMenu
{
public:
	GameMenu(SDL_Renderer* ren);
	~GameMenu();

	void Event(SDL_Event& event);
	MenuResult Update();
	void Render();
	
private:
	SDL_Renderer* renderer;
	SDL_Texture* menu_texture;
	SDL_Rect srcrect, desrect;
	SettingButton* set;
	MainButton* main_button;
	RestartButton* restart;
	ResumeButton* resume;
	XButton* xbutton;
};
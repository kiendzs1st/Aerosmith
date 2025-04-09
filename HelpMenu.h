#pragma once
#include "StartMenu.h"
#include"XButton.h"
#include"Animation.h"

class HelpMenu
{
public:
	HelpMenu(SDL_Renderer* ren);
	~HelpMenu();

	void Event(SDL_Event& event);
	MenuResult Update();
	void Render();
private:
	XButton* xbutton = nullptr;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect Srcrect, Desrect;

};
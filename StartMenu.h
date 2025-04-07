#pragma once
#include <SDL.h>
#include <unordered_map>
#include "TextureManagement.h"
#include "button.h"
#include "Font.h"
#include <string>

class StartMenu
{
public:
	StartMenu(SDL_Renderer* ren);
	~StartMenu();

	void Event(SDL_Event& event);
	void Update();
	void Render();

	bool Status(string id);
private:

	SDL_Renderer* renderer;
	SDL_Texture* texture;
	unordered_map<string, SDL_Rect> button_dest;
	unordered_map<string, bool> status_store;

	Button* start ;
	Button* settings ;
	Button* help ;
	Button* quit ;
};
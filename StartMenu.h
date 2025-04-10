#pragma once
#include <SDL.h>
#include <unordered_map>
#include "TextureManagement.h"
#include "button.h"
#include "Font.h"
#include <string>

enum class MenuResult
{
	NONE,
	STARTMENU,
	START,
	RESTART,
	HELP,
	QUIT,
	SETTINGS
};

class StartMenu
{
public:
	StartMenu(SDL_Renderer* ren);
	~StartMenu();

	virtual void Event(SDL_Event& event);
	virtual MenuResult Update();
	virtual void Render();

	virtual bool& Status(string id);
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
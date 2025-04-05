#pragma once
#include <SDL.h>
#include "TextureManagement.h"
#include <unordered_map>
#include <string>

class Button
{
public:
	static Button& GetInstance();
	~Button();

	void LoadButton(const char* filename, const char* id, int xpos, int ypos, SDL_Renderer* ren);
	void Update();
	void Event();
	void Render();

private:
	Button();

	unordered_map<string, SDL_Texture*> button_store;
	unordered_map<string, int> x_store;
	unordered_map<string, int> y_store;


	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect srcrect, desrect;

};
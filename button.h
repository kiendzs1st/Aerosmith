#pragma once
#include <SDL.h>
#include "TextureManagement.h"
#include <unordered_map>
#include <string>

class Button
{
public:
	Button( int xpos, int ypos, SDL_Renderer* ren);
	~Button();

	void Update();
	void Event(SDL_Event& event);
	void Render();

	SDL_Rect GetRect();

private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect desrect;

	bool IsHovered;
	bool IsPressed;
};
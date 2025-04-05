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
	bool IsPressed();
	bool IsHovered();

	SDL_Rect GetRect();

private:
	SDL_Renderer* renderer;
	SDL_Texture* normal;
	SDL_Texture* hover;
	SDL_Texture* pressed;
	SDL_Rect desrect;

	bool is_hovered;
	bool is_pressed;
};
#pragma once
#include "TextureManagement.h"
#include "Animation.h"
#include "Enemies.h"
#include "Player.h"
#include <string>
class Player;

class Drop
{
public:
	Drop(const char* filename, SDL_Renderer* ren, Enemies* enemies);
	~Drop();

	bool CheckCollison(SDL_Rect a, SDL_Rect b);
	int Boost();
	void Update();
	void Render();

	double GetY();
	SDL_Rect DropHitBox();

private:
	double xpos, ypos;
	std::string drop_object;

	SDL_Renderer* renderer;
	SDL_Texture* text;
	SDL_Rect srcrect, desrect;
	SDL_Rect DropHitbox;
};
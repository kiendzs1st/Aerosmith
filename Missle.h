#pragma once
#include "TextureManagement.h"
#include "Animation.h"
#include "Player.h"
#include "Enemies.h"
#include <SDL.h>

class Player;

class Enemies;

class Missile
{
public:
	Missile(const char* filename, SDL_Renderer* ren, Player * player);
	~Missile();

	void MissileUpdate();
	void RenderMissile();
	int GetY();
	int GetX();
	void misDestroy();

	SDL_Rect& GetMrect();

private:
	double x, y;
	double velocity;
	static constexpr int width = 19;
	static constexpr int height = 20;
	bool MissileCollision = false;
		 
	SDL_Renderer* RenMis;
	SDL_Texture* TextMis;
	SDL_Rect srcrec, desrec;
};
#pragma once
#include "TextureManagement.h"
#include "Enemies.h"
#include "SDL.h"

class Enemies;

class EnemiesBullet
{
public:
	EnemiesBullet(const char* filename, SDL_Renderer* ren, Enemies * enemies);
	~EnemiesBullet();

	void BulletUpdate();
	void BulletRender();

	double GetY();
	int& Velocity();

	SDL_Rect& GetBulletRect();

private:
	double xpos, ypos;
	int velocity = 3;
	const double width = 39;
	const double height = 40;
	bool IsActive = false;

	SDL_Rect src, dest;
	SDL_Renderer* bulletren;
	SDL_Texture* bulltext;
};

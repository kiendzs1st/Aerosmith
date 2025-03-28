#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Drop.h"
#include <vector>

class Drop;

class Game {
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool Collision(SDL_Rect a, SDL_Rect b);
	void CheckCollision();
	bool running() { return isRunning; }
	static SDL_Renderer* renderer;
	
private :
	SDL_Rect EnemiesView;
	Uint32 lastMissileFrame = SDL_GetTicks();
	SDL_Window* window;

	std::vector<Drop*> drop_store;
	int score = 0;
	int wave = 1;
	int health = 3;
	int EneHealth = 3;
	int BulletDelayFrame = 0;
	int BulletSpeed = 4;
	bool isRunning;
	bool IsMisExplose;
	bool IsEneExplose;
	bool IsRespawning;
};
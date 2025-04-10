#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Drop.h"
#include <vector>
#include <string>

class Drop;

enum class GameState
{
	StartMenu,
	Help,
	Starting,
	Settings1,
	GameMenu,
	GameOver,
	Quit
};

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
	void Restart();
	int LoadHighScore();
	void UpdateHighScore();
	bool running() { return isRunning; }
	static SDL_Renderer* renderer;
	
private :
	SDL_Rect EnemiesView;
	Uint32 lastMissileFrame = SDL_GetTicks();
	SDL_Window* window;

	std::vector<Drop*> drop_store;
	int bgY1 = 0;
	int bgY2 = -720;	

	const int bgHeight = 2160;
	int score = 0;
	int highscore;
	std::string score_string = "Score:0";
	std::string wave_string = "Wave:1";
	std::string life_string = "3x";
	int wave = 0;
	int health = 3;
	int EneHealth = 3;
	int BulletDelayFrame = 0;
	int BulletSpeed = 4;
	int MusicX = 726 ;
	int SoundX = 726 ;
	bool isRunning;
	bool IsMisExplose;
	bool IsEneExplose;
	bool IsRespawning;
	bool IsScoring;
	bool IsStarting = false;
	bool IsSettingOpened = false;
	bool FirstWave = true;
	int count = 0;
	std::string mname = "assets/music/background1.mp3";

	GameState current_state;
};
#pragma once
#include "Game.h"
#include "TextureManagement.h"
#include "Enemies.h"
#include "Missle.h"
#include <random>

using namespace std;

class Player;

class Map
{
public:
	Map(SDL_Renderer* ren, int ene_health, int BulletDelay, int BulletVelo);
	~Map();

	void LoadMap(Player* player);
	void DrawMap();
	void MapUpdateEnemies();
	void MapRenderEnemies();

	int& GetCount();

	vector<Enemies*>& GetEstore();

private:
	SDL_Rect src, dest;
	SDL_Texture *Enemy;
	vector<Enemies*> estore;
	SDL_Renderer* render;
	vector<int> ScoreStorage;

	int EneHealth;
	int BulletDelayTime;
	int BulletSpeed;
	const int row = 4;
	const int column = 11;
	int count = row * column;
};

#include "Tilemap.h"

extern Missile* missle;

using namespace std;

int layout[5][11] = { 0 };


Map::Map(SDL_Renderer* ren, int ene_health, int BulletDelay, int BulletVelo)
{
	render = ren;
	EneHealth = ene_health;
	BulletDelayTime = BulletDelay;
	BulletSpeed = BulletVelo;
}

Map::~Map()
{
	for (auto x : estore)
	{
		delete x;
	}

	estore.clear();
}

void Map::LoadMap(Player* player)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(1, 3);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			layout[i][j] = dist(gen);
		}
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (layout[i][j] == 1)
			{
				estore.emplace_back(new Enemies("assets/ufo.png", render, i, j, 5, EneHealth, BulletDelayTime, BulletSpeed, player));
			}
			if (layout[i][j] == 2)
			{
				estore.emplace_back(new Enemies("assets/ufo1.png", render, i, j, 5,EneHealth, BulletDelayTime, BulletSpeed, player));
			}
			if (layout[i][j] == 3)
			{
				estore.emplace_back(new Enemies("assets/alien.png", render, i, j, 5,EneHealth, BulletDelayTime, BulletSpeed, player));
			}
		}
	}
}

void Map::DrawMap()
{
	
}

void Map::MapUpdateEnemies()
{
	for (auto it = estore.begin();it != estore.end(); it++)
	{
		(*it)->EnemiesUpdate();
	}
}
void Map::MapRenderEnemies()
{
	for (auto it = estore.begin(); it != estore.end(); it++)
	{
		(*it)->RenderEnemies();
	}
}

vector<Enemies*>& Map::GetEstore()
{
	return estore;
}

int& Map::GetCount()
{
	return count;
}

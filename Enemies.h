#pragma once
#include "TextureManagement.h"
#include "EnemiesBullet.h"
#include <SDL.h>
#include "Animation.h"
#include "Missle.h"
#include "Player.h"
#include <cstdlib>
#include <vector>
#include <string>
#include "Tilemap.h"


class Player;

class EnemiesBullet;

class Missile;

class Enemies
{
public:
	Enemies(const char* filename, SDL_Renderer* ren, int i, int j, int frame_num,int ene_health, int bullet_delay, Player* playerptr);
	~Enemies();

	void EnemiesUpdate();
	void RenderEnemies();
	void eneDestroy();
	void IsDamaged();
	void FireBullet(Enemies& enemy);

	bool Collision(SDL_Rect& a, SDL_Rect& b);
	double GetX();
	double GetY();
	int getHealth();
	int GetEValue();
	bool& GetPlayerStatus();
	bool IsEneAppeared();
	
	SDL_Rect& GetErect();
	SDL_Rect& GetEsrc();

	
private:
	double expos, eypos;
	int FrameNum;
	int EneHealth;
	bool IsPlayerDamaged;
	bool appear = false;
	int EnemiesValue;
	int BulletDelayTime;

	std::string link;
	std::vector<EnemiesBullet*> BulletStore;
	SDL_Rect EneHitbox;
	EnemiesBullet* bullet;
	SDL_Renderer* eren;
	SDL_Texture* etext;
	SDL_Rect esrc, edes;
	

};
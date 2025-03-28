#pragma once
#include "TextureManagement.h"
#include "Animation.h"
#include "Missle.h"
#include "Enemies.h"
#include <vector>

class Enemies;

class Missile;

class Player
{
public :


	Player(const char* titlesheet, SDL_Renderer* ren);
	~Player();
	
	void PlayerEvent(SDL_Event& event);
	void PlayerUpdate();
	void PlayerRender();

	std::vector<Missile*>& GetMstore();

	double GetX();
	double GetY();
	bool& GetPlayerStatus();
	bool PlayerIsDamaged();
	bool& IsAniWork();
	bool IsAppeared();
	int& GetVelo();
	int& GetFCD();
	int& GetDame();

	SDL_Rect& getPlayerRect();
	SDL_Rect GetSrcRect();
	SDL_Rect GetDesRect();

private:
	double xpos, ypos;
	double Speedx, Speedy;
	bool keys[322] = { false };
	std::vector<Missile*> MissileStore;
	int FireCoolDown = 15;

	SDL_Renderer* RenderPlayer;
	SDL_Texture* PlayerTexture;
	SDL_Rect srcrc, desrc;
	SDL_Rect PlayerHitBox;

	bool firstappear = true;
	bool IsAnimationWorking = true;
	bool PlayerStatus;
	bool IsPlayerDamaged;
	int NumFrames = 4;
	int x_origin;
	int y_origin;
	int velocity = 5;
	int fcd = 0;
	int damage = 1;
};

extern Player* player;
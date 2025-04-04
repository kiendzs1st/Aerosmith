﻿	#include "Game.h"
	#include "TextureManagement.h"
	#include "Player.h"
	#include "Missle.h"
	#include "tilemap.h"
	#include "Music.h"
	#include "Font.h"
	#include "Animation.h"
	#include "StartMenu.h"

	using namespace std;

	SDL_Renderer* Game::renderer = nullptr;

	SDL_Rect srcrect, desrect;
	SDL_Rect MisColliDes;
	SDL_Rect MisColliSrc = {0, 0, 35, 20};
	SDL_Rect EneColliSrc, EneColliDes;
	SDL_Rect PlayerColliDes, PlayerColliSrc;
	SDL_Rect HeartRect = { 920, 665, 105 , 60 };

	Missile* missle = nullptr;
	Player* player = nullptr;
	Map* map = nullptr;	
	StartMenu* start_menu = nullptr;

	Animation ExploAni1 = { 35, 20 };
	Animation ExploAni2 = { 64, 64 };
	Animation ExploAni3 = { 64, 64 };
	
	SDL_Texture* playerTex;
	SDL_Texture* Explosion1 = nullptr;
	SDL_Texture* Explosion2 = nullptr;
	SDL_Texture* Explosion3 = nullptr;
	SDL_Texture* Background = nullptr;
	SDL_Texture* Heart = nullptr;
	
	Uint32 MisAnimationStart = SDL_GetTicks();
	Uint32 EneAnimationStart = SDL_GetTicks();
	Uint32 PlayerExploStart = SDL_GetTicks();
	Uint32 RespawnTime = SDL_GetTicks();
	Uint32 LoadingLayout = SDL_GetTicks();
	Uint32 AnimationDelay = 500;

	Game::Game()
	{
	}
	Game :: ~Game()
	{
	}
	void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
		int flags = 0;
		if (fullscreen) {
			flags = SDL_WINDOW_SHOWN;
		}
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
			cout << SDL_GetError();
			isRunning = false;
		}
		else {
			window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
			SDL_SetWindowBordered(window, SDL_TRUE);
			if (!window) {
				cout << SDL_GetError();
			}
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (!renderer) {
				cout << SDL_GetError();
			}
			else {
				SDL_SetRenderDrawColor ( renderer,  0,0,0,255 );
			}
			isRunning = true;
		
		}

		if (TTF_Init() == -1) {
			cout << TTF_GetError();
			isRunning = false;
		}


		if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) == -1) {
			cout << SDL_GetError();
			isRunning = false;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
			cout << Mix_GetError();
			isRunning = false;
		}

		EnemiesView = { 100, 0, width, height};

		player = new Player("assets/texture/jett.png", renderer);
		missle = new Missile("assets/texture/missle.png", renderer, player);
		map = new Map(renderer, EneHealth, BulletDelayFrame, BulletSpeed);
		start_menu = new StartMenu(renderer);
		map->LoadMap(player);

		Explosion1 = TextureMana::TextureLoader("assets/texture/explosion1.png", renderer);
		Explosion2 = TextureMana::TextureLoader("assets/texture/explosion2.png", renderer);
		Explosion3 = TextureMana::TextureLoader("assets/texture/explosion3.png", renderer);
		Background = TextureMana::TextureLoader("assets/texture/bg4.png", renderer);
		Heart = TextureMana::TextureLoader("assets/texture/heart.png", renderer);

		Music::GetInstance().SoundLoader("hit", "assets/music/hit.mp3");
		Music::GetInstance().SoundLoader("explosion", "assets/music/explosion1.mp3");
		Music::GetInstance().SoundLoader("ting", "assets/music/ting.mp3");
		Music::GetInstance().MusicLoader("background1", "assets/music/background1.mp3");

		Font::GetInstance().LoadFont("score", "assets/font/VT323-Regular.ttf", score_string.c_str(), 28, 255, 255, 255, 100, 680, renderer);
		Font::GetInstance().LoadFont("life", "assets/font/VT323-Regular.ttf", life_string.c_str(), 28, 255, 255, 255, 920, 680, renderer);
	}


	void Game::handleEvents() {

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
				return;
			}
			if (start_menu->Status("start") == false)
			{
				start_menu->Event(event);
			}
			else
			{
				player->PlayerEvent(event);
			}
		}
	}

	bool Game::Collision(SDL_Rect a, SDL_Rect b)
	{
		int leftA, leftB;
		int rightA, rightB;
		int topA, topB;
		int bottomA, bottomB;

		leftA = a.x;
		rightA = a.x + a.w;
		topA = a.y;
		bottomA = a.y + a.h;

		leftB = b.x;
		rightB = b.x + b.w;
		topB = b.y;
		bottomB = b.y + b.h;

		if (leftA >= rightB)
		{
			return false;
		}
		if (rightA <= leftB)
		{
			return false;
		}
		if (bottomA <= topB)
		{
			return false;
		}
		if (topA >= bottomB)
		{
			return false;
		}

		return true;
	}



	void Game::CheckCollision()
	{
		auto& MisStore = player->GetMstore();
		auto& EneStore = map->GetEstore();
		for (auto mis = MisStore.begin(); mis != MisStore.end();)
		{
			bool MissileDestroyed = false;
			SDL_Rect misrect = (*mis)->GetMrect();

			for (auto ene = EneStore.begin(); ene != EneStore.end();)
			{
				SDL_Rect enerect = (*ene)->GetErect();
				bool DamageEnemies = false;
				if (Collision(misrect, enerect))
				{

					MisColliDes = { misrect.x, misrect.y - 15, MisColliSrc.w, MisColliSrc.h };

					if (!IsMisExplose)
					{
						IsMisExplose = true;
						MisAnimationStart = SDL_GetTicks();
					}
					
					DamageEnemies = true;
					if (DamageEnemies)
					{
						(*ene)->IsDamaged();
						Music::GetInstance().PlaySound("hit");
					}

					(*mis)->misDestroy();
					delete *mis;
					mis = MisStore.erase(mis);

					if ((*ene)->getHealth() <= 0)
					{
						Music::GetInstance().PlaySound("explosion");

						EneColliSrc = (*ene)->GetEsrc();
						EneColliDes = (*ene)->GetErect();
						EneColliDes.x += 6;
						score_string += to_string(score);

						if (rand() % 100 < 5)
						{
							int itemchoices = rand() % 4 + 1;
							if (itemchoices == 1)
							{
								drop_store.emplace_back(new Drop("assets/texture/heart.png", renderer, (*ene)));
							}
							if (itemchoices == 2)
							{
								drop_store.emplace_back(new Drop("assets/texture/speed.png", renderer, (*ene)));
							}
							if (itemchoices == 3)
							{
								drop_store.emplace_back(new Drop("assets/texture/velo.png", renderer, (*ene)));
							}
							if (itemchoices == 4)
							{
								drop_store.emplace_back(new Drop("assets/texture/damage.png", renderer, (*ene)));
							}
						}

						score += (*ene)->GetEValue();
						score_string.erase(6);
						score_string += to_string(score);
						Font::GetInstance().LoadFont("score", "assets/font/VT323-Regular.ttf", score_string.c_str(), 28, 255, 255, 255, 100, 680, renderer);

						(*ene)->eneDestroy();
						delete* ene;
						ene = EneStore.erase(ene);
						map->GetCount()--;
						if (!IsEneExplose)
						{
							IsEneExplose = true;
							EneAnimationStart = SDL_GetTicks();
						}
					}
					MissileDestroyed = true;
					break;
				}
				else
				{
					ene++;
				}
			}
			if (!MissileDestroyed)
			{
				mis++;
			}
		}

	}
	void Game::update() 
	{
		if (start_menu->Status("start") == false)
		{
		start_menu->Update();
		}
		else
		{
			bgY1 += player->GetVelo();
			bgY2 += player->GetVelo();
			if (bgY1 >= 720) {
				bgY1 = bgY2 - 720;
			}
			if (bgY2 >= 720) {
				bgY2 = bgY1 - 720;
			}

			if (Mix_PlayingMusic() == 0)
			{
				Music::GetInstance().PlayMusic("background1");
			}
			desrect.h = desrect.w = 32;
			player->PlayerUpdate();
			if ((player->PlayerIsDamaged() && health > 0))
			{
				health--;
				life_string.erase(0);
				life_string = to_string(health) + "x";
				Font::GetInstance().LoadFont("life", "assets/font/VT323-Regular.ttf", life_string.c_str(), 28, 255, 255, 255, 920, 680, renderer);
				Music::GetInstance().PlaySound("explosion");

				cout << health << endl;
				PlayerColliDes = player->GetDesRect();
				PlayerColliSrc = player->GetSrcRect();

				if (!player->IsAniWork())
				{
					PlayerExploStart = SDL_GetTicks();
					player->IsAniWork() = true;
				}

				delete player;
				player = new Player("assets/texture/jett.png", renderer);
			}

			missle->MissileUpdate();
			map->MapUpdateEnemies();
			for (auto drop = drop_store.begin(); drop != drop_store.end(); )
			{
				if ((*drop)->CheckCollison(player->getPlayerRect(), (*drop)->DropHitBox()))
				{

					Music::GetInstance().PlaySound("ting");

					if ((*drop)->Boost() == 1 && health < 5)
					{
						health++;
						life_string.erase(0);
						life_string = to_string(health) + "x";
						Font::GetInstance().LoadFont("life", "assets/font/VT323-Regular.ttf", life_string.c_str(), 28, 255, 255, 255, 920, 680, renderer);
					}
					if ((*drop)->Boost() == 2 && player->GetVelo() < 10)
					{
						player->GetVelo()++;
					}
					if ((*drop)->Boost() == 3 && player->GetDame() < EneHealth)
					{
						player->GetDame()++;
					}
					if ((*drop)->Boost() == 4 && player->GetFCD() < 10)
					{
						player->GetFCD()++;
					}

					delete* drop;
					drop = drop_store.erase(drop);
				}
				else if ((*drop)->GetY() > 720)
				{
					delete* drop;
					drop = drop_store.erase(drop);
				}
				else
				{
					(*drop)->Update();
					drop++;
				}
			}
			if (IsMisExplose)
			{
				if (SDL_GetTicks() - MisAnimationStart < AnimationDelay)
				{
					ExploAni1.Define(4);
				}
				else
				{
					IsMisExplose = false;
				}
			}

			if (IsEneExplose)
			{
				if (SDL_GetTicks() - EneAnimationStart < AnimationDelay)
				{
					ExploAni2.Define(4);
				}
				else
				{
					IsEneExplose = false;
				}
			}

			if (player->IsAniWork())
			{
				if (SDL_GetTicks() - PlayerExploStart < 800)
				{
					ExploAni3.Define(4);
				}
				else
				{
					player->IsAniWork() = false;
				}
			}


			if (map->GetCount() == 0 && !IsRespawning)
			{
				IsRespawning = true;
				RespawnTime = SDL_GetTicks();
			}

			if (IsRespawning && SDL_GetTicks() - RespawnTime > 2000)
			{
				wave++;
				wave_string.erase(5);
				wave_string += to_string(wave);
				cout << "Wave : " << wave << endl;
				if (wave % 2 == 0)
				{
					if (EneHealth < 10)
					{
						EneHealth++;
						cout << "Enemies' health: " << EneHealth << endl;
					}
					if (BulletDelayFrame <= 2000)
					{
						BulletDelayFrame += 500;
						cout << "BulletCoolDown: " << 3000 - BulletDelayFrame << endl;
					}
					if (BulletSpeed < 10)
					{
						BulletSpeed += 2;
						cout << "Bullet Speed: " << BulletSpeed << endl;
					}
				}
				delete map;
				map = new Map(renderer, EneHealth, BulletDelayFrame, BulletSpeed);
				map->LoadMap(player);
				IsRespawning = false;

				LoadingLayout = SDL_GetTicks();
			}
			int ypos = 680 - Font::GetInstance().GetH("score");
			Font::GetInstance().LoadFont("wave", "assets/font/VT323-Regular.ttf", wave_string.c_str(), 28, 255, 255, 255, 100, ypos, renderer);

			if (wave == 1)
			{
				if (SDL_GetTicks() - LoadingLayout > 5000)
				{
					CheckCollision();
				}
			}
			else
			{
				if (SDL_GetTicks() - LoadingLayout > 3000)
				{
					CheckCollision();
				}
			}
		}
	}

	void Game::render() 
	{
		SDL_RenderClear(renderer);
		if (start_menu->Status("start") == false)
		{
			start_menu->Render();
		}
		else
		{
			SDL_Rect bgRect1 = { 0, bgY1, 1080, 720 };
			SDL_Rect bgRect2 = { 0, bgY2 , 1080, 720 };
			SDL_RenderCopy(renderer, Background, NULL, &bgRect1);
			SDL_RenderCopy(renderer, Background, NULL, &bgRect2);
			SDL_RenderSetViewport(renderer, &EnemiesView);
			map->MapRenderEnemies();
			SDL_RenderSetViewport(renderer, NULL);

			Font::GetInstance().Render("score");
			Font::GetInstance().Render("wave");
			Font::GetInstance().Render("life");

			SDL_RenderCopy(renderer, Heart, NULL, &HeartRect);

			for (auto drop = drop_store.begin(); drop != drop_store.end(); drop++)
			{
				(*drop)->Render();
			}

			if (IsMisExplose)
			{
				ExploAni1.AniRen(MisColliSrc, MisColliDes, renderer, Explosion1);
			}

			if (IsEneExplose)
			{

				ExploAni2.AniRen(EneColliSrc, EneColliDes, renderer, Explosion2);
			}

			if (player->IsAniWork())
			{
				ExploAni3.AniRen(PlayerColliSrc, PlayerColliDes, renderer, Explosion3);
			}

			player->PlayerRender();
		}
		SDL_RenderPresent(renderer);
	}

	void Game::clean() {

		delete map;
		delete player;

		Mix_Quit();
		IMG_Quit();
		TTF_Quit();
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();

	}



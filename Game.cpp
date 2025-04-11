#include "Game.h"
#include "TextureManagement.h"
#include "Player.h"
#include "Missle.h"
#include "tilemap.h"
#include "Music.h"
#include "Font.h"
#include "Animation.h"
#include "StartMenu.h"
#include "HelpMenu.h"
#include "Settings.h"
#include "GameMenu.h"
#include "GameOver.h"
#include <fstream>
#include <vld.h>

using namespace std;

SDL_Renderer* Game::renderer = nullptr;

SDL_Rect srcrect, desrect;
SDL_Rect MisColliDes;
SDL_Rect MisColliSrc = { 0, 0, 35, 20 };
SDL_Rect EneColliSrc, EneColliDes;
SDL_Rect PlayerColliDes, PlayerColliSrc;
SDL_Rect HeartRect = { 920, 665, 105 , 60 };
SDL_Rect Srcrect = { 0, 0, 1000, 720 };
SDL_Rect Desrect = { 0, 0, Srcrect.w + 80, Srcrect.h };

Player* player = nullptr;
Map* map = nullptr;
StartMenu* start_menu = nullptr;
HelpMenu* helpping_menu = nullptr;
Settings* setting_menu = nullptr;
GameMenu* game_menu = nullptr;
GameOver* game_over = nullptr;
string highscore_string = "";

Animation ExploAni1 = { 35, 20 };
Animation ExploAni2 = { 64, 64 };
Animation ExploAni3 = { 64, 64 };
Animation HelpAni = { 1000, 720 };

SDL_Texture* playerTex;
SDL_Texture* Explosion1 = nullptr;
SDL_Texture* Explosion2 = nullptr;
SDL_Texture* Explosion3 = nullptr;
SDL_Texture* Background = nullptr;
SDL_Texture* Heart = nullptr;
SDL_Texture* starttexture = nullptr;

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
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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

	EnemiesView = { 100, 0, width, height };
	highscore = LoadHighScore();
	highscore_string = "HighScore:" + std::to_string(highscore);
	current_state = GameState::StartMenu;
	start_menu = new StartMenu(renderer);
	Music::GetInstance().MusicLoader("startmenu", "assets/music/startmenu.mp3");

	Font::GetInstance().LoadFont("wave", "assets/font/VT323-Regular.ttf", wave_string.c_str(), 28, 255, 255, 255, 100, 624, renderer);
	Font::GetInstance().LoadFont("life", "assets/font/VT323-Regular.ttf", life_string.c_str(), 28, 255, 255, 255, 920, 680, renderer);
	Font::GetInstance().LoadFont("score", "assets/font/VT323-Regular.ttf", score_string.c_str(), 28, 255, 255, 255, 100, 652, renderer);
	Font::GetInstance().LoadFont("highscore", "assets/font/VT323-Regular.ttf", highscore_string.c_str(), 28, 255, 255, 255, 100, 680, renderer);
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
		if (current_state == GameState::StartMenu)
		{
			start_menu->Event(event);
		}
		if (current_state == GameState::Settings1)
		{
			setting_menu->Event(event);
		}
		if (current_state == GameState::Help)
		{
			helpping_menu->Event(event);
		}
		if (current_state == GameState::GameOver)
		{
			game_over->Event(event);
		}
		if (current_state == GameState::Starting && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			current_state = GameState::GameMenu;
		}
		else if (current_state == GameState::GameMenu)
		{
			if (game_menu)
			{
				game_menu->Event(event);
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			{
				if (game_menu)
				{
					delete game_menu;
					game_menu = nullptr;
				}
				current_state = GameState::Starting;
			}
		}
		if (IsStarting)
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
				delete* mis;
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
					Font::GetInstance().Update(score_string.c_str(), "score");

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
	if (current_state == GameState::StartMenu)
	{
		start_menu->Update();
		if (Mix_PlayingMusic() == 0)
		{
			Music::GetInstance().PlayMusic("startmenu");
		}
		LoadingLayout = SDL_GetTicks();
		MenuResult result = start_menu->Update();
		if (result == MenuResult::START)
		{
			IsStarting = true;
			player = new Player("assets/texture/jett.png", renderer);
			map = new Map(renderer, EneHealth, BulletDelayFrame, BulletSpeed);
			map->LoadMap(player);
			Music::GetInstance().SoundLoader("hit", "assets/music/hit.mp3");
			Music::GetInstance().SoundLoader("explosion", "assets/music/explosion1.mp3");
			Music::GetInstance().SoundLoader("ting", "assets/music/ting.mp3");
			Music::GetInstance().MusicLoader("background", mname.c_str());

			Explosion1 = TextureMana::TextureLoader("assets/texture/explosion1.png", renderer);
			Explosion2 = TextureMana::TextureLoader("assets/texture/explosion2.png", renderer);
			Explosion3 = TextureMana::TextureLoader("assets/texture/explosion3.png", renderer);
			Background = TextureMana::TextureLoader("assets/texture/bg4.png", renderer);
			Heart = TextureMana::TextureLoader("assets/texture/heart.png", renderer);
			current_state = GameState::Starting;
			delete start_menu;
			start_menu = nullptr;
			LoadingLayout = SDL_GetTicks();
		}
		if (result == MenuResult::HELP)
		{
			VLDReportLeaks();
			helpping_menu = new HelpMenu(renderer);
			current_state = GameState::Help;
			delete start_menu;
			start_menu = nullptr;
		}
		if (result == MenuResult::SETTINGS)
		{
			current_state = GameState::Settings1;
			starttexture = TextureMana::TextureLoader("assets/texture/start_menu.png", renderer);
			setting_menu = new Settings(MusicX, SoundX,renderer);
			delete start_menu;
			start_menu = nullptr;
		}
		if (result == MenuResult::QUIT)
		{
			isRunning = false;
		}
	}
	if (current_state == GameState::Help)
	{
		MenuResult result = helpping_menu->Update();
		if (result == MenuResult::START)
		{
			start_menu = new StartMenu(renderer);
			current_state = GameState::StartMenu;
			delete helpping_menu;
			helpping_menu = nullptr;
		}
	}
	if (current_state == GameState::Settings1)
	{
		MenuResult result = setting_menu->Update();
		MusicX = setting_menu->MusicDes();
		SoundX = setting_menu->SoundDes();
		if (setting_menu->MusicName() != "")
		{
			mname = setting_menu->MusicName();
			Music::GetInstance().CleanMusic("background");
			Music::GetInstance().MusicLoader("background", mname.c_str());

		}
		if (setting_menu->IsChange())
		{
			Music::GetInstance().MusicVolume(setting_menu->MusicPercent());
			Music::GetInstance().SoundVolume(setting_menu->SoundPercent());
		}

		if (result == MenuResult::START)
		{
			start_menu = new StartMenu(renderer);
			if (IsStarting)
			{
				current_state = GameState::GameMenu;
			}
			else
			{
				current_state = GameState::StartMenu;
			}
			if (IsStarting && game_menu == nullptr)
			{
				game_menu = new GameMenu(renderer);
			}
			delete setting_menu;
			setting_menu = nullptr;
			SDL_DestroyTexture(starttexture);
		}
	} 
	if (current_state == GameState::GameOver)
	{
		Music::GetInstance().CleanMusic("background");
		SDL_DestroyTexture(Explosion1);
		SDL_DestroyTexture(Explosion2);
		SDL_DestroyTexture(Explosion3);
		SDL_DestroyTexture(Background);
		SDL_DestroyTexture(Heart);
		MenuResult result = game_over->Update();
		if (result == MenuResult::STARTMENU)
		{
			current_state = GameState::StartMenu;
			start_menu = new StartMenu(renderer);
			Restart();
			Music::GetInstance().MusicLoader("startmenu", "assets/music/startmenu.mp3");
			Music::GetInstance().PlayMusic("startmenu");
			delete game_over;
			game_over = nullptr;
		}
		if (result == MenuResult::RESTART)
		{
			current_state = GameState::Starting;
			IsStarting = true;
			Music::GetInstance().MusicLoader("background", mname.c_str());
			Explosion1 = TextureMana::TextureLoader("assets/texture/explosion1.png", renderer);
			Explosion2 = TextureMana::TextureLoader("assets/texture/explosion2.png", renderer);
			Explosion3 = TextureMana::TextureLoader("assets/texture/explosion3.png", renderer);
			Background = TextureMana::TextureLoader("assets/texture/bg4.png", renderer);
			Heart = TextureMana::TextureLoader("assets/texture/heart.png", renderer);
			Restart();
			delete game_over;
			game_over = nullptr;
		}
	}
	if (current_state == GameState::GameMenu && game_menu == nullptr)

	{
		game_menu = new GameMenu(renderer);
	}
	if (IsStarting)
	{
		if (current_state == GameState::GameMenu)
		{
			MenuResult result = game_menu->Update();
			if (result == MenuResult::START)
			{
				current_state = GameState::Starting;
				delete game_menu;
				game_menu = nullptr;
			}
			if (result == MenuResult::SETTINGS)
			{
				current_state = GameState::Settings1;
				setting_menu = new Settings(MusicX, SoundX, renderer);
				delete game_menu;
				game_menu = nullptr;
			}
			if (result == MenuResult::RESTART)
			{
				cout << 1 << endl;
				Music::GetInstance().CleanMusic("background");
				Music::GetInstance().MusicLoader("background", mname.c_str());
				Restart();
				current_state = GameState::Starting;
				delete game_menu;
				game_menu = nullptr;
			}
			if (result == MenuResult::STARTMENU)
			{
				Restart();
				delete game_menu;
				game_menu = nullptr;

				if (setting_menu)
				{
					delete setting_menu;
					setting_menu = nullptr;
				}
				if (start_menu)
				{
					delete start_menu;
					start_menu = nullptr;
				}

				current_state = GameState::StartMenu;
				start_menu = new StartMenu(renderer);
				IsStarting = false;
			}
		}

		if (start_menu && current_state == GameState::Starting)
		{
			delete start_menu;
			start_menu = nullptr;
		}
		if (current_state == GameState::Settings1)
		{
			setting_menu->Update();
		}
		if (current_state == GameState::Starting)
		{
			Music::GetInstance().CleanMusic("startmenu");
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
				Music::GetInstance().PlayMusic("background");
			}
			desrect.h = desrect.w = 32;
			player->PlayerUpdate();
			if (score > highscore)
			{
				highscore_string.erase(10);
				highscore_string += to_string(score);
				Font::GetInstance().Update(highscore_string.c_str(), "highscore");
			}
			if ((player->PlayerIsDamaged() && health > 0))
			{
				health--;
				life_string.erase(0);
				life_string = to_string(health) + "x";
				Font::GetInstance().Update(life_string.c_str(), "life");
				Music::GetInstance().PlaySound("explosion");

				cout << health << endl;
				PlayerColliDes = player->GetDesRect();
				PlayerColliSrc = player->GetSrcRect();

				if (health == 0)
				{
					UpdateHighScore();
					game_over = new GameOver(renderer, score, highscore);
					highscore_string.erase(10);
					highscore_string += to_string(highscore);
					Font::GetInstance().Update(highscore_string.c_str(), "highscore");
					IsStarting = false;
					current_state = GameState::GameOver;
				}

				if (!player->IsAniWork())
				{
					PlayerExploStart = SDL_GetTicks();
					player->IsAniWork() = true;
				}

				delete player;
				player = new Player("assets/texture/jett.png", renderer);
			}
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
				Font::GetInstance().Update(wave_string.c_str(), "wave");
				if (wave % 2 == 0)
				{
					if (EneHealth < 10)
					{
						EneHealth++;
					}
					if (BulletDelayFrame <= 2000 && 3000 - BulletDelayFrame > 1000)
					{
						BulletDelayFrame += 500;
					}
					if (BulletSpeed < 10)
					{
						BulletSpeed += 2;
					}
				}
				delete map;
				map = new Map(renderer, EneHealth, BulletDelayFrame, BulletSpeed);
				map->LoadMap(player);
				IsRespawning = false;
				LoadingLayout = SDL_GetTicks();
			}
			if (wave <= 1)
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
}

void Game::render()
{
	SDL_RenderClear(renderer);
	if (current_state == GameState::StartMenu)
	{
			start_menu->Render();
	}
	if (current_state == GameState::Help)
	{
		helpping_menu->Render();
	}
	if (current_state == GameState::Settings1)
	{
		SDL_RenderCopy(renderer, starttexture, NULL, NULL);
		setting_menu->Render();
	}
	if (current_state == GameState::GameOver)
	{
		game_over->Render();
	}
	if (IsStarting)
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
		Font::GetInstance().Render("highscore");

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
		if (current_state == GameState::GameMenu && game_menu != nullptr)
		{
			game_menu->Render();
		}
		if (current_state == GameState::Settings1)
		{
			setting_menu->Render();
		}
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	delete map;
	delete player;
	if (start_menu)
	{
		delete start_menu;
	}
	if (helpping_menu)
	{
		delete helpping_menu;
	}
	if (setting_menu)
	{
		delete setting_menu;
	}
	if (game_menu)
	{
		delete game_menu;
	}
	if (game_over)
	{
		delete game_over;
	}
	SDL_DestroyTexture(playerTex);
	SDL_DestroyTexture(Explosion1);
	SDL_DestroyTexture(Explosion2);
	SDL_DestroyTexture(Explosion3);
	SDL_DestroyTexture(Background);
	SDL_DestroyTexture(Heart);
	SDL_DestroyTexture(starttexture);

	Music::GetInstance().CleanAll();
	Font::GetInstance().CleanAll();

	if (drop_store.size() != 0)
	{
		for (auto& d : drop_store)
		{
			delete d;
		}
		drop_store.clear();
	}

	mname.clear();
	score_string.clear();
	life_string.clear();
	wave_string.clear();

	Font::GetInstance().CleanAll();
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::Restart()
{
	score_string = "Score:0";
	wave_string = "Wave:1";
	life_string = "3x";
	score = 0;
	this->wave = 1;
	health = 3;
	EneHealth = 3;
	BulletDelayFrame = 0;
	BulletSpeed = 4;
	LoadingLayout = SDL_GetTicks();
	delete map;
	map = new Map(renderer, EneHealth, BulletDelayFrame, BulletSpeed);
	map->LoadMap(player);
	delete player;
	player = new Player("assets/texture/jett.png", renderer);
	if (drop_store.size() != 0)
	{
		for (auto& d : drop_store)
		{
			delete d;
		}
		drop_store.clear();
	}
	
	Font::GetInstance().Update(score_string.c_str(), "score");
	Font::GetInstance().Update(highscore_string.c_str(), "highscore");
	Font::GetInstance().Update(wave_string.c_str(), "wave");
	Font::GetInstance().Update(life_string.c_str(), "life");
}

int Game::LoadHighScore()
{
	std::ifstream file("data/highscore.txt");
	int tmp = 0;
	if (file.is_open())
	{
		file >> tmp;
		file.close();
	}
	return tmp;
}

void Game::UpdateHighScore() {
	if (score > highscore) {
		highscore = score;
		std::ofstream file("data/highscore.txt");
		if (file.is_open()) {
			file << highscore;
			file.close();
		}
	}
}
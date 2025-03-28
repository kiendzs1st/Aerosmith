#include "Enemies.h"

const int tile_size = 64;
const int spacing = 16;
const int row = 5;
const int column = 11;

Animation EniAni = { 64, 64 };

EnemiesBullet* bullet = nullptr;


Enemies::Enemies(const char* filename, SDL_Renderer* ren, int i, int j, int frame_num, int ene_health, int bullet_delay, int bullet_velo, Player* playerptr)
{
	eren = ren;
	etext = TextureMana::TextureLoader(filename, eren);
	expos =  j * ( tile_size + spacing) ;
	eypos = i * ( tile_size + spacing) ;
	esrc = { 0, 0, 64, 64 };
	if (i % 2 != 0)
	{
		edes = { -1000 , (int)eypos, esrc.w , esrc.h };
	}
	else
	{
		edes = { 1000 , (int)eypos, esrc.w , esrc.h };
	}

	FrameNum = frame_num;

	EneHitbox = { (int)expos + 94, (int)eypos, 64, 64 };


	player = playerptr;

	link = filename;

	EneHealth = ene_health;

	BulletDelayTime = bullet_delay;

	bullet_speed = bullet_velo;

	bullet = new EnemiesBullet("assets/lazer.png",eren, bullet_speed, this);
}
 
void Enemies::eneDestroy()
{
	if (etext)
	{
		SDL_DestroyTexture(etext);
		etext = nullptr;
	}
}

Enemies::~Enemies()
{
	delete bullet;
	eneDestroy();
}


bool Enemies::Collision(SDL_Rect& a, SDL_Rect& b)
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


void Enemies::FireBullet(Enemies& enemy)
{
		BulletStore.emplace_back(new EnemiesBullet("assets/lazer.png", eren, bullet_speed, this));
}

void Enemies::EnemiesUpdate()
{
	if (!player->IsAppeared())
	{
		if (edes.x < expos)
		{
			edes.x += 10;
		}
		else if (edes.x > expos)
		{
			edes.x -= 10;
		}
		else
		{
			appear = true;
		}
	}

	EniAni.Define(FrameNum);

	if (appear)
	{
		if (rand() % (3000 - BulletDelayTime) < 1)
		{
			FireBullet(*this);
		}
		SDL_Rect PlayerRect = player->getPlayerRect();

		for (auto bullet = BulletStore.begin(); bullet != BulletStore.end();)
		{

			SDL_Rect BulletRect = (*bullet)->GetBulletRect();

			if (Collision(PlayerRect, BulletRect))
			{
				delete* bullet;
				bullet = BulletStore.erase(bullet);
				player->GetPlayerStatus() = true;
			}

			else if ((*bullet)->GetY() > 720)
			{

				delete* bullet;
				bullet = BulletStore.erase(bullet);


			}
			else
			{
				(*bullet)->BulletUpdate();
				bullet++;
			}
		}
	}
}

void Enemies::RenderEnemies()
{
	EniAni.AniRen(esrc, edes, eren, etext);
	for (auto bullet = BulletStore.begin(); bullet != BulletStore.end(); bullet++)
	{	
		(*bullet)->BulletRender();
	}

}


double Enemies::GetX()
{
	return expos;
}

double Enemies::GetY()
{
	return eypos;
}

SDL_Rect& Enemies::GetErect()
{
	return EneHitbox;
}

SDL_Rect& Enemies::GetEsrc()
{
	return esrc;
}

void Enemies::IsDamaged()
{
	EneHealth -= player->GetDame();
}

int Enemies::getHealth()
{
	return EneHealth;
}

bool& Enemies::GetPlayerStatus()
{
	return IsPlayerDamaged;
}

int Enemies::GetEValue()
{
	if (link == "assets/ufo.png")
	{
		return 100;
	}
	else if (link == "assets/ufo1.png")
	{
		return 200;
	}
	else
	{
		return 300;
	}
}

bool Enemies :: IsEneAppeared()
{
	return appear;
}
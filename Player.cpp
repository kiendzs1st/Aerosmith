#include "Player.h"
#include "TextureManagement.h"



using namespace std;

Animation PlayerAni1 = { 64, 64 };
Animation PlayerAni2 = { 64, 64 };


Player::Player(const char* titlesheet, SDL_Renderer* ren)
{
	RenderPlayer = ren;
	PlayerTexture = TextureMana::TextureLoader(titlesheet, ren);

	xpos = 1080 / 2;
	ypos = 800;
	x_origin = 64 / 2;
	y_origin = 64 / 2;

	srcrc = { 0, 0, 64, 64 };
	desrc = { (int) xpos - x_origin, (int) ypos - y_origin ,srcrc.w, srcrc.h}; 
	PlayerHitBox = { desrc.x - 94, desrc.y, desrc.w - 20, desrc.h };

	Music::GetInstance().SoundLoader("shoot", "assets/music/lasergun.mp3");
}

Player::~Player()
{

}

void Player::PlayerEvent(SDL_Event& event)
{

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym > 0 && event.key.keysym.sym < 322)
		{
			keys[event.key.keysym.sym] = true;
		}
		
	}

	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym > 0 && event.key.keysym.sym < 322)
		{
			keys[event.key.keysym.sym] = false;
		}
	}
}


void Player::PlayerUpdate()
{
	if (firstappear)
	{
		if (desrc.y > 600)
		{
			ypos -= 2;
			desrc.y = ypos - y_origin;
			PlayerHitBox.y = desrc.y;
			return;
		} 
		else
		{
			firstappear = false;
		}
	}
	else {

		Speedx = Speedy = 0;

		if (PlayerStatus == true)
		{
			IsPlayerDamaged = true;
			PlayerStatus = false;
		}
		else
		{
			IsPlayerDamaged = false;
		}

		if (keys[SDLK_w]) Speedy += -velocity;
		if (keys[SDLK_s]) Speedy += velocity;
		if (keys[SDLK_d]) Speedx += velocity;
		if (keys[SDLK_a]) Speedx += -velocity;
		if (keys[SDLK_SPACE])
		{
			if (FireCoolDown == 0)
			{
				Music::GetInstance().PlaySound("shoot");
				MissileStore.emplace_back(new Missile("assets/texture/missle.png", RenderPlayer, this));
				FireCoolDown = 15 - fcd;
			}
		}

		xpos += Speedx;
		ypos += Speedy;

		if (xpos < 100) xpos = 100;
		if (ypos < 720 / 2) ypos = 720 / 2;
		if (xpos + desrc.w > 1000) xpos = 1000 - desrc.w;
		if (ypos + desrc.h > 720) ypos = 720 - desrc.h;

		desrc.x = (int)xpos - x_origin;
		desrc.y = (int)ypos - y_origin;
		PlayerHitBox.x = desrc.x - 94;
		PlayerHitBox.y = desrc.y;

		PlayerAni1.Define(4);

		if (FireCoolDown > 0)
		{
			FireCoolDown--;
		}

		for (auto it = MissileStore.begin(); it != MissileStore.end();)
		{
			(*it)->MissileUpdate();

			if ((*it)->GetY() < 0)
			{
				delete* it;
				it = MissileStore.erase(it);
			}
			else {
				it++;
			}
		}
	}
}

void Player::PlayerRender()
{
	PlayerAni1.AniRen(srcrc, desrc, RenderPlayer, PlayerTexture);

	for (auto& it : MissileStore)
	{
		it->RenderMissile();
	}
}

vector<Missile*>& Player::GetMstore()
{
	return MissileStore;
}

double Player::GetX()
{
	return xpos;
}

double Player::GetY()
{
	return ypos;
}

SDL_Rect& Player::getPlayerRect()
{
	return PlayerHitBox;
}

SDL_Rect Player::GetSrcRect()
{
	return srcrc;
}

SDL_Rect Player::GetDesRect()
{
	return desrc;
}

bool& Player::GetPlayerStatus()
{
	return PlayerStatus;
}

bool Player::PlayerIsDamaged()
{
	return IsPlayerDamaged;
}

bool& Player::IsAniWork()
{
	return IsAnimationWorking;
}

bool Player::IsAppeared()
{
	return firstappear;
}

int& Player::GetVelo()
{
	return velocity;
}
int& Player::GetFCD()
{
	return fcd;
}

int& Player::GetDame()
{
	return damage;
}
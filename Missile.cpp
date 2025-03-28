#include "Missle.h"

Animation MisAni = { 19, 20 };


Missile::Missile(const char* filename, SDL_Renderer* ren, Player * player)
{
	RenMis = ren;
	TextMis = TextureMana::TextureLoader(filename, ren);
	velocity = -10;
	x = player->GetX() + 64 / 2 - 64 / 2 - 10; 
	y = player->GetY() - 15;

	srcrec = { 0, 0, width, height };
	desrec = { (int)x, (int)y, 19, 20 };
}

void Missile::misDestroy()
{
	if (TextMis)
	{
		SDL_DestroyTexture(TextMis);
		TextMis = nullptr;
	}
}

Missile::~Missile()
{
	misDestroy();
}



void Missile::MissileUpdate()
{
	
		MisAni.Define(2);
		y += velocity;
		desrec.y = (int)y;
		desrec.x = (int)x;
}



void Missile::RenderMissile()
{
	
	SDL_Rect tmpsrc = srcrec;
	MisAni.AniRen(tmpsrc, desrec, RenMis, TextMis);
}

int Missile::GetY()
{
	return desrec.y;
}

int Missile::GetX()
{
	return desrec.x;
}


SDL_Rect& Missile::GetMrect()
{
	return desrec;
}
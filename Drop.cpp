#include "Drop.h"

using namespace std;

Animation DropAni = { 35, 20 };

Drop::Drop(const char* filename, SDL_Renderer* ren, Enemies* enemies)
{
	renderer = ren;
	text = TextureMana::TextureLoader(filename, renderer);
	xpos = xpos = enemies->GetErect().x - 85;
	ypos = enemies->GetErect().y + 10;
	drop_object = filename;

	srcrect = { 0, 0, 32, 20 };
	desrect = { (int)xpos, (int)ypos, srcrect.w, srcrect.h };
	DropHitbox = { desrect.x, desrect.y, desrect.w, desrect.h };
}

Drop::~Drop()
{
	SDL_DestroyTexture(text);
}

bool Drop::CheckCollison(SDL_Rect a, SDL_Rect b)
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

int Drop::Boost()
{
	if (drop_object == "assets/heart.png")
	{
		return 1;
	}
	else if (drop_object == "assets/speed.png")
	{
		return 2;
	}
	else if (drop_object == "assets/damage.png")
	{
		return 3;
	}
	else if (drop_object == "assets/velo.png")
	{
		return 4;
	}
	return 0;
}

void Drop::Update()
{
	ypos += 2;
	desrect.y = (int)ypos;
	desrect.x = (int)xpos + 106;
	DropHitbox.x = desrect.x - 106;
	DropHitbox.y = desrect.y;
}

void Drop::Render()
{
	SDL_RenderCopy(renderer, text, &srcrect, &desrect);
}

SDL_Rect Drop::DropHitBox()
{
	return DropHitbox;
}

double Drop::GetY()
{
	return ypos;
}
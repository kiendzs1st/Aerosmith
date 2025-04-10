#include "geats.h"

Geats::Geats(int x, int y, SDL_Renderer* ren) : Button(x, y, ren)
{
	normal = TextureMana::TextureLoader("assets/texture/geats1.png", renderer);
	hover = TextureMana::TextureLoader("assets/texture/geats2.png", renderer);
	pressed = TextureMana::TextureLoader("assets/texture/geats3.png", renderer);
	desrect = { x, y, 124, 66 };
}

Geats::~Geats()
{
	SDL_DestroyTexture(normal);
	SDL_DestroyTexture(hover);
	SDL_DestroyTexture(pressed);
}
#include "jojo.h"

Jojo::Jojo(int x, int y, SDL_Renderer* ren) : Button(x, y, ren)
{
	normal = TextureMana::TextureLoader("assets/texture/jojo1.png", renderer);
	hover = TextureMana::TextureLoader("assets/texture/jojo2.png", renderer);
	pressed = TextureMana::TextureLoader("assets/texture/jojo3.png", renderer);
	desrect = { x, y, 124, 66 };
}

Jojo::~Jojo()
{
	SDL_DestroyTexture(normal);
	SDL_DestroyTexture(hover);
	SDL_DestroyTexture(pressed);
}
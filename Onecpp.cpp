#include "One.h"

One::One(int x, int y, SDL_Renderer* ren) : Button(x, y, ren)
{
	normal = TextureMana::TextureLoader("assets/texture/one1.png", renderer);
	hover = TextureMana::TextureLoader("assets/texture/one2.png", renderer);
	pressed = TextureMana::TextureLoader("assets/texture/one3.png", renderer);
	desrect = { x, y, 124, 66 };
}

One::~One()
{
	SDL_DestroyTexture(normal);
	SDL_DestroyTexture(hover);
	SDL_DestroyTexture(pressed);
}
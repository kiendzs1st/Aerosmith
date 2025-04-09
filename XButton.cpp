#include "XButton.h"
#include "TextureManagement.h"

XButton::XButton(int x, int y, SDL_Renderer* ren) : Button(x, y, ren)
{
	normal = TextureMana::TextureLoader("assets/texture/x_normal.png", renderer);
	hover = TextureMana::TextureLoader("assets/texture/x_hover.png", renderer);
	pressed = TextureMana::TextureLoader("assets/texture/x_pressed.png", renderer);
}

XButton::~XButton()
{
	SDL_DestroyTexture(normal);
	SDL_DestroyTexture(hover);
	SDL_DestroyTexture(pressed);
}
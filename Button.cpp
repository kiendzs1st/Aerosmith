#include "button.h"

Button::Button()
{
}

Button::~Button()
{
}

Button& Button::GetInstance()
{
	static Button instance;
	return instance;
}

void Button::LoadButton(const char* filename, const char* id, int xpos, int ypos, SDL_Renderer* ren)
{
	renderer = ren;
	texture = TextureMana::TextureLoader(filename, renderer);
	button_store[id] = texture;
	x_store[id] = xpos;
	y_store[id] = ypos;
	srcrect = { 0, 0, 256, 128 };
	desrect = { x_store[id], y_store[id], srcrect.w, srcrect.h };
}

void Button::Event()
{

}

void Button::Update()
{

}

void Button::Render()
{

}
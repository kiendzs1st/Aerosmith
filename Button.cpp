#include "button.h"

Button::Button( int xpos, int ypos, SDL_Renderer* ren)
{
	renderer = ren;
	texture = TextureMana::TextureLoader("assets/texture/normal_button.png", renderer);
	desrect = { xpos, ypos, 256,  128 };
}

Button::~Button()
{
}

void Button::Event(SDL_Event& event)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	SDL_Point MousePoint = { mouseX, mouseY };
	if (SDL_PointInRect(&MousePoint, &desrect))
	{
		IsHovered = true;
	}
	else
	{
		IsHovered = false;
	}

	if (event.type == SDL_MOUSEBUTTONDOWN && SDL_PointInRect(&MousePoint, &desrect))
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			IsPressed = true;
		}
	}
	if (event.type == SDL_MOUSEBUTTONUP && SDL_PointInRect(&MousePoint, &desrect))
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			IsPressed = false;
		}
	}
}

void Button::Update()
{
	if (IsHovered)
	{
		SDL_DestroyTexture(texture);
		texture = TextureMana::TextureLoader("assets/texture/hover_button.png", renderer);
	}
	else
	{
		texture = TextureMana::TextureLoader("assets/texture/normal_button.png", renderer);
	}

	if (IsPressed)
	{
		SDL_DestroyTexture(texture);
		texture = TextureMana::TextureLoader("assets/texture/pressed_button.png", renderer);
	}
	
}

void Button::Render()
{
	SDL_RenderCopy(renderer, texture, nullptr, &desrect);
}

SDL_Rect Button::GetRect()
{
	return desrect;
}
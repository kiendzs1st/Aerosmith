#include "button.h"

Button::Button( int xpos, int ypos, SDL_Renderer* ren)
{
	renderer = ren;
	normal = TextureMana::TextureLoader("assets/texture/normal_button.png", renderer);
	hover = TextureMana::TextureLoader("assets/texture/hover_button.png", renderer);
	pressed = TextureMana::TextureLoader("assets/texture/pressed_button_1.png", renderer);
	desrect = { xpos, ypos, 256,  128 };
}

Button::~Button()
{
	SDL_DestroyTexture(normal);
	SDL_DestroyTexture(hover);
	SDL_DestroyTexture(pressed);
}


void Button::Event(SDL_Event& event)
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	SDL_Point MousePoint = { mouseX, mouseY };
	if (SDL_PointInRect(&MousePoint, &desrect))
	{
		is_hovered = true;
	}
	else
	{
		is_hovered = false;
	}

	if (event.type == SDL_MOUSEBUTTONDOWN && SDL_PointInRect(&MousePoint, &desrect))
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			is_pressed = true;
		}
	}
	if (event.type == SDL_MOUSEBUTTONUP && SDL_PointInRect(&MousePoint, &desrect))
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			is_pressed = false;
			is_working = true;
		}
	}
}

void Button::Update()
{	
}

void Button::Render()
{
	if (is_hovered)
	{
		SDL_RenderCopy(renderer, hover, nullptr, &desrect);
		if (is_pressed)
		{
			SDL_RenderCopy(renderer, pressed, nullptr, &desrect);
		}
	}
	else
	{
		SDL_RenderCopy(renderer, normal, nullptr, &desrect);
	}
}

SDL_Rect Button::GetRect()
{
	return desrect;
}

bool Button::IsHovered()
{
	return is_hovered;
}

bool Button::IsPressed()
{
	return is_working;
}
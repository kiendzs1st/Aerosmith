#include "ButtonStore.h"

SettingButton::SettingButton(int x, int  y, SDL_Renderer* ren) : Button(x, y, ren)
{
	normal = TextureMana::TextureLoader("assets/texture/set_normal.png", renderer);
	hover = TextureMana::TextureLoader("assets/texture/set_hover.png", renderer);
	pressed = TextureMana::TextureLoader("assets/texture/set_pressed.png", renderer);
}

SettingButton::~SettingButton()
{
	SDL_DestroyTexture(normal);
	SDL_DestroyTexture(hover);
	SDL_DestroyTexture(pressed);
}

MainButton::MainButton(int x, int y, SDL_Renderer* ren) : Button(x, y, ren)
{
	normal = TextureMana::TextureLoader("assets/texture/main_normal.png", renderer);
	hover = TextureMana::TextureLoader("assets/texture/main_hover.png", renderer);
	pressed = TextureMana::TextureLoader("assets/texture/main_pressed.png", renderer);
}

MainButton::~MainButton()
{
	SDL_DestroyTexture(normal);
	SDL_DestroyTexture(hover);
	SDL_DestroyTexture(pressed);
}

RestartButton::RestartButton(int x, int y, SDL_Renderer* ren) : Button(x, y, ren)
{
	normal = TextureMana::TextureLoader("assets/texture/restart_normal.png", renderer);
	hover = TextureMana::TextureLoader("assets/texture/restart_hover.png", renderer);
	pressed = TextureMana::TextureLoader("assets/texture/restart_pressed.png", renderer);
}

RestartButton::~RestartButton()
{
	SDL_DestroyTexture(normal);
	SDL_DestroyTexture(hover);
	SDL_DestroyTexture(pressed);
}

ResumeButton::ResumeButton(int x, int y, SDL_Renderer* ren) : Button(x, y, ren)
{
	normal = TextureMana::TextureLoader("assets/texture/resume_normal.png", renderer);
	hover = TextureMana::TextureLoader("assets/texture/resume_hover.png", renderer);
	pressed = TextureMana::TextureLoader("assets/texture/resume_pressed.png", renderer);
}

ResumeButton::~ResumeButton()
{
	SDL_DestroyTexture(normal);
	SDL_DestroyTexture(hover);
	SDL_DestroyTexture(pressed);
}
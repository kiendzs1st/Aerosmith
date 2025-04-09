#include "HelpMenu.h"

Animation help_menu_ani = { 1000, 720 };

HelpMenu::HelpMenu(SDL_Renderer* ren)
{
	renderer = ren;
	texture = TextureMana::TextureLoader("assets/texture/help_menu.png", renderer);
	xbutton = new XButton(800, 65, renderer);
	Srcrect = { 0, 0, 1000, 720 };
	Desrect = { 0, 0, Srcrect.w + 80, Srcrect.h };
}

HelpMenu::~HelpMenu()
{
	SDL_DestroyTexture(texture);
	delete xbutton;
}

void HelpMenu::Event(SDL_Event& event)
{
	xbutton->Event(event);
}

MenuResult HelpMenu::Update()
{
	help_menu_ani.Define(4);
	if (xbutton->IsPressed())
	{
		return MenuResult::START;
	}
	return MenuResult::NONE;
}

void HelpMenu::Render()
{
	help_menu_ani.AniRen(Srcrect, Desrect, renderer, texture);
	xbutton->Render();
}
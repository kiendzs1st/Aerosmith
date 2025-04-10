#include "GameMenu.h"
#include <iostream>

GameMenu::GameMenu( SDL_Renderer* ren)
{
	renderer = ren;
	menu_texture = TextureMana::TextureLoader("assets/texture/gamemenu.png", renderer);
	srcrect = { 0, 0, 680, 520 };
	desrect = { 200, 100, srcrect.w, srcrect.h };
	xbutton = new XButton(750, 120, renderer);
	resume = new ResumeButton(262, 250, renderer);
	restart = new RestartButton(562, 250, renderer);
	set = new SettingButton(262, 450, renderer);
	main_button = new MainButton(562, 450, renderer);

	std::cout << "Generated successfully" << std::endl;
}

GameMenu::~GameMenu()
{
	SDL_DestroyTexture(menu_texture);
	delete set;
	delete restart;
	delete resume;
	delete main_button;
	delete xbutton;
	std::cout << "Destroy" << std::endl;
}

void GameMenu::Event(SDL_Event& event)
{
	set->Event(event);
	restart->Event(event);
	resume->Event(event);
	main_button->Event(event);
	xbutton->Event(event);
}

MenuResult GameMenu::Update()
{
	if (xbutton->IsPressed() || resume ->IsPressed())
	{
		return MenuResult::START;
	}
	if (set->IsPressed())
	{
		return MenuResult::SETTINGS;
	}
	if (main_button->IsPressed())
	{
		return MenuResult::STARTMENU;
	}
	if (restart->IsPressed())
	{
		return MenuResult::RESTART;
	}
	return MenuResult::NONE;
}

void GameMenu::Render()
{
	SDL_RenderCopy(renderer, menu_texture, &srcrect, &desrect);
	set->Render();
	restart->Render();
	resume->Render();
	main_button->Render();
	xbutton->Render();
}
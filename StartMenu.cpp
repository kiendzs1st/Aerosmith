#include "StartMenu.h"

Button* start = nullptr;
Button* settings = nullptr;
Button* help = nullptr;
Button* quit = nullptr;

StartMenu::StartMenu(SDL_Renderer* ren)
{
	renderer = ren;
	texture = TextureMana::TextureLoader("assets/texture/start_menu.png", renderer);
	start = new Button(270, 350, renderer);
	settings = new Button(550, 350, renderer);
	help = new Button(270, 500, renderer);
	quit = new Button(550, 500, renderer);

	button_dest["start"] = start->GetRect();
	button_dest["settings"] = settings->GetRect();
	button_dest["help"] = help->GetRect();
	button_dest["quit"] = quit->GetRect();

	Font::GetInstance().LoadFont("start", "assets/font/VT323-Regular.ttf", "start", 70, 255, 255, 255, 327 , 355, renderer);
}

StartMenu::~StartMenu()
{

}

void StartMenu::Event(SDL_Event& event)
{
	start->Event(event);
	settings->Event(event);
	help->Event(event);
	quit->Event(event);
}

void StartMenu::Update()
{
	start->Update();
	settings->Update();
	help->Update();
	quit->Update();
}

void StartMenu::Render()
{
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	start->Render();
	settings->Render();
	help->Render();
	quit->Render();
	Font::GetInstance().Render("start");
}
#include "StartMenu.h"

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

	Font::GetInstance().LoadFont("start", "assets/font/VT323-Regular.ttf", "Start", 64, 255, 255, 255, 335, 362, renderer);
	Font::GetInstance().LoadFont("settings", "assets/font/VT323-Regular.ttf", "Settings", 64, 255, 255, 255, 575, 362, renderer);
	Font::GetInstance().LoadFont("help", "assets/font/VT323-Regular.ttf", "Help", 64, 255, 255, 255, 350, 515, renderer);
	Font::GetInstance().LoadFont("quit", "assets/font/VT323-Regular.ttf", "Quit", 64, 255, 255, 255, 627, 515, renderer);
}

StartMenu::~StartMenu()
{
	delete start;
	delete settings;
	delete help;
	delete quit;

	Font::GetInstance().Clean();

	for (auto& pair : button_dest)
	{
		
	}

	SDL_DestroyTexture(texture);
}


void StartMenu::Event(SDL_Event& event)
{
	start->Event(event);
	settings->Event(event);
	help->Event(event);
	quit->Event(event);
}

MenuResult StartMenu::Update()
{
	if (start->IsHovered())
	{
		Font::GetInstance().ChangeColor("start", 242, 232, 28);
		if (start->IsPressed())
		{
			return MenuResult::START;
		}
	}
	else
	{
		Font::GetInstance().ChangeColor("start", 255, 255, 255);
	}

	if (settings->IsHovered())
	{
		Font::GetInstance().ChangeColor("settings", 242, 232, 28);
		if (settings->IsPressed())
		{
			return MenuResult::SETTINGS;
		}
	}
	else
	{
		Font::GetInstance().ChangeColor("settings", 255, 255, 255);
	}

	if (help->IsHovered())
	{
		Font::GetInstance().ChangeColor("help", 242, 232, 28);
		if (help->IsPressed())
		{
			return MenuResult::HELP;
		}
	}
	else
	{
		Font::GetInstance().ChangeColor("help", 255, 255, 255);
	}
	if (quit->IsHovered())
	{
		Font::GetInstance().ChangeColor("quit", 242, 232, 28);
		if (quit->IsPressed())
		{
			return MenuResult::QUIT;
		}
	}
	else
	{
		Font::GetInstance().ChangeColor("quit", 255, 255, 255);
	}
}

void StartMenu::Render()
{
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	start->Render();
	settings->Render();
	help->Render();
	quit->Render();

	Font::GetInstance().Render("start");
	Font::GetInstance().Render("settings");
	Font::GetInstance().Render("help");
	Font::GetInstance().Render("quit");
}

bool& StartMenu::Status(string id)
{
	return status_store[id];
}
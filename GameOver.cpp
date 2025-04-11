#include "GameOver.h"

GameOver::GameOver(SDL_Renderer* ren, int score, int highscore)
{
	renderer = ren;
	texture = TextureMana::TextureLoader("assets/texture/gameover.png", renderer);
	mainmenu = new MainButton(412, 350, renderer);
	restart = new RestartButton(412, 500, renderer);
	string score_string = "Your Score: " + to_string(score);
	string highscore_string = "Highest Score: " + to_string(highscore);
	Font::GetInstance().LoadFont("finalscore", "assets/font/VT323-Regular.ttf", score_string.c_str(), 50, 255, 255, 255, 360, 250, renderer);
	Font::GetInstance().LoadFont("finalhighscore", "assets/font/VT323-Regular.ttf", highscore_string.c_str(), 50, 255, 255, 255, 360, 300, renderer);
}

GameOver::~GameOver()
{
	SDL_DestroyTexture(texture);
	delete mainmenu;
	delete restart;
	Font::GetInstance().Clean("finalscore");
	Font::GetInstance().Clean("finalhighscore");
}

void GameOver::Event(SDL_Event& event)
{
	mainmenu->Event(event);
	restart->Event(event);
}

MenuResult GameOver::Update()
{
	if (mainmenu->IsPressed())
	{
		return MenuResult::STARTMENU;
	}
	if (restart->IsPressed())
	{
		return MenuResult::RESTART;
	}
	return MenuResult::NONE;
}

void GameOver::Render()
{
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	mainmenu->Render();
	restart->Render();
	Font::GetInstance().Render("finalscore");
	Font::GetInstance().Render("finalhighscore");
}
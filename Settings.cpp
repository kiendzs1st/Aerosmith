#include "Settings.h"

Settings::Settings(SDL_Renderer* ren)
{
	renderer = ren;
	texture = TextureMana::TextureLoader("assets/texture/setting.png", renderer);
	srcrect = { 0, 0, 680, 520 };
	desrect = { 200, 100, 680, 520 };
	xbutton = new XButton( 500, 120,renderer);
	Volume::GetInstance().LoadChanger("Music", 490, 300, renderer);
	Volume::GetInstance().LoadChanger("Sound", 490, 400, renderer);

	Font::GetInstance().LoadFont("Music", "assets/font/VT323-Regular.ttf", "Music Volume ", 32, 255, 255, 255, 300, 285, renderer);
	Font::GetInstance().LoadFont("Sound", "assets/font/VT323-Regular.ttf", "Sound Volume", 32, 255, 255, 255, 300, 385, renderer);
}

Settings::~Settings()
{
	SDL_DestroyTexture(texture);
	delete xbutton;
	Font::GetInstance().Clean();
}

void Settings::Event(SDL_Event& event)
{
	Volume::GetInstance().Event("Music", event);
	Volume::GetInstance().Event("Sound", event);
}

void Settings::Update()
{
	Volume::GetInstance().Update("Music");
	Volume::GetInstance().Update("Sound");
	if (Volume::GetInstance().IsPressed("Music") || Volume::GetInstance().IsPressed("Sound"))
	{
		is_change = true;
		music_percent = Volume::GetInstance().Percentvolume("Music");
		sound_percent = Volume::GetInstance().Percentvolume("Sound");
	}
	else
	{
		is_change = false;
	}
}

void Settings::Render()
{
	SDL_RenderCopy(renderer, texture, &srcrect, &desrect);
	Font::GetInstance().Render("Music");
	Volume::GetInstance().Render("Music");
	Font::GetInstance().Render("Sound");
	Volume::GetInstance().Render("Sound");
}

bool Settings::IsChange()
{
	return is_change;
}

float Settings::MusicPercent()
{
	return music_percent;
}

float Settings::SoundPercent()
{
	return sound_percent;
}
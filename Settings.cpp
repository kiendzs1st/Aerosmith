#include "Settings.h"
#include <iostream>

Settings::Settings(int MusicX, int SoundX, SDL_Renderer* ren)
{
	renderer = ren;
	texture = TextureMana::TextureLoader("assets/texture/setting.png", renderer);
	srcrect = { 0, 0, 680, 520 };
	desrect = { 200, 100, 680, 520 };
	name_rect = { 580, 480, 124, 66 };
	xbutton = new XButton( 750, 120,renderer);
	geats = new Geats(480,465, renderer);
	jojo = new Jojo(720, 465, renderer);
	one = new One(600, 465, renderer);
	Volume::GetInstance().LoadChanger("Music", MusicX, 300, renderer);
	Volume::GetInstance().LoadChanger("Sound", SoundX,400, renderer);

	std::cout << "Created" << std::endl;
}

Settings::~Settings()
{
	SDL_DestroyTexture(texture);
	delete geats;
	delete one;
	delete jojo;
	delete xbutton;
	
	std::cout << "Destroyed" << std::endl;
}

void Settings::Event(SDL_Event& event)
{
	Volume::GetInstance().Event("Music", event);
	Volume::GetInstance().Event("Sound", event);
	xbutton->Event(event);
	jojo->Event(event);
	geats->Event(event);
	one->Event(event);
}

MenuResult Settings::Update()
{
	if (xbutton->IsPressed())
	{
		return MenuResult::START;
	}
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
	return MenuResult::NONE;
}

string Settings::MusicName()
{
	if (jojo->IsPressed())
	{
		return music_name[0];
	}
	else if (geats->IsPressed())
	{
		return music_name[1];
	}
	else if (one->IsPressed())
	{
		return music_name[2];
	}
	else
	{
		return "";
	}
}

void Settings::Render()
{
	SDL_RenderCopy(renderer, texture, &srcrect, &desrect);
	xbutton->Render();
	jojo->Render();
	one->Render();
	geats->Render();

	Volume::GetInstance().Render("Music");
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

int Settings::MusicDes()
{
	return Volume::GetInstance().GetX("Music");
}

int Settings::SoundDes()
{
	return Volume::GetInstance().GetX("Sound");
}
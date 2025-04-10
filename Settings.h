#pragma once
#include <SDL.h>
#include "StartMenu.h"
#include "TextureManagement.h"
#include "XButton.h"
#include "Volume.h"
#include "Font.h"
#include <vector>
#include "geats.h"
#include "jojo.h"
#include"One.h"


class Settings
{
public:
	Settings(int MusicX, int SoundX,SDL_Renderer* ren);
	~Settings();

	void Event(SDL_Event& event) ;
	MenuResult Update() ;
	void Render() ;

	bool IsChange();
	float MusicPercent();
	float SoundPercent();
	int MusicDes();
	int SoundDes();

	string MusicName();


protected:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect srcrect, desrect;
	SDL_Rect name_rect;
	XButton* xbutton;
	Jojo* jojo;
	Geats* geats;
	One* one;
	bool is_change;
	float music_percent;
	float sound_percent;
	int position = 0;

	vector<string> music_name = { "assets/music/background1.mp3",
								 "assets/music/background2.mp3",
								 "assets/music/background3.mp3" };
};
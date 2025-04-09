#pragma once
#include <SDL.h>
#include "TextureManagement.h"
#include "XButton.h"
#include "Volume.h"
#include "Font.h"

class Settings
{
public:
	Settings( SDL_Renderer* ren);
	~Settings();

	void Event(SDL_Event& event);
	void Update();
	void Render();

	bool IsChange();
	float MusicPercent();
	float SoundPercent();

protected:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect srcrect, desrect;
	XButton* xbutton;
	bool is_change;
	float music_percent;
	float sound_percent;
};
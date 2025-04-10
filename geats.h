#pragma once
#include "button.h"

class Geats : public Button
{
public: 
	Geats(int x, int y, SDL_Renderer* ren);
	~Geats();
};
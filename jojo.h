#pragma once
#include "button.h"

class Jojo : public Button
{
public:
	Jojo(int x, int y, SDL_Renderer* ren);
	~Jojo();
};
#pragma once
#include "button.h"

class XButton : public Button
{
public:
	XButton(int x, int y, SDL_Renderer* ren);
	~XButton();
};
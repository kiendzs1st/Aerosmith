#pragma once
#include "button.h"

class SettingButton : public Button
{
public:
	SettingButton(int x, int y, SDL_Renderer* ren);
	~SettingButton();
private:
};

class MainButton : public Button
{
public: 
	MainButton(int x, int y, SDL_Renderer* ren);
	~MainButton();
private:

};

class RestartButton : public Button
{
public:
	RestartButton(int x, int y, SDL_Renderer* ren);
	~RestartButton();
private:

};

class ResumeButton : public Button
{
public:
	ResumeButton(int x, int y, SDL_Renderer* ren);
	~ResumeButton();
};
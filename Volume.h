#pragma once
#include <SDL.h>
#include "TextureManagement.h"
#include <unordered_map>
#include <string>

class Volume
{
public:
	static Volume& GetInstance();
	~Volume();

	void LoadChanger( const char* id, int xpos, int ypos, SDL_Renderer* ren);
	void Event(const char* id, SDL_Event& Event);
	void Update(const char* id);
	float Percentvolume(const char* id);
	void Render(const char* id);

	bool IsPressed(string id);
	int GetX(string id);

private:
	Volume();

	SDL_Renderer* renderer;
	SDL_Texture* normal_thumb;
	SDL_Texture* hover_thumb;
	SDL_Texture* bar;
	unordered_map<string, int > x_store;
	unordered_map<string, int> y_store;
	unordered_map<string, bool> is_hover;
	unordered_map<string, bool> is_pressed;
	unordered_map<string, SDL_Rect> des_store;
	unordered_map<string, SDL_Rect> bar_store;
	SDL_Rect srcrect;
	SDL_Rect barsrc;
	SDL_Point MousePoint;
};
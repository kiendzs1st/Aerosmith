#pragma once
#include<SDL.h>
#include<SDL_ttf.h>
#include <string>
#include <unordered_map>

using namespace std;

class Font
{
public:
	~Font();
	static Font& GetInstance();	

	void LoadFont(const char* id,const char* filename, const char* text, int FontSize, int r, int g, int b, int xpos, int ypos, SDL_Renderer* ren);
	void Render(string id);
	int GetW(string id);
	int GetH(string id);

private:
	Font();
	unordered_map<string, SDL_Texture*> map;
	unordered_map<string, int> w_store;
	unordered_map<string, int> h_store;
	unordered_map<string, SDL_Rect> rect_store;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* TextSur = nullptr;
	SDL_Texture* FontText = nullptr;
	TTF_Font* font = nullptr;
	SDL_Rect FontRect;
};
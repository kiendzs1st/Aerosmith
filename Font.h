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
	void Update(const char* text, string id);
	void ChangeColor(string id, int r, int g, int b);
	int GetW(string id);
	int GetH(string id);
	void Clean(string id);
	void CleanAll();

private:
	Font();
	unordered_map<string, TTF_Font*> font_store;
	unordered_map<string, SDL_Texture*> map;
	unordered_map<string, int> w_store;
	unordered_map<string, int> h_store;
	unordered_map<string, SDL_Rect> rect_store;
	unordered_map<string, SDL_Color> color_store;
	unordered_map<string, string> text_store;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* TextSur = nullptr;
	SDL_Texture* FontText = nullptr;
	SDL_Rect FontRect;
};
#include "Font.h"


Font::Font()
{

}

Font::~Font()
{
}

Font& Font::GetInstance()
{
	static Font instance;
	return instance;
}

void Font::LoadFont(const char* id,const char* filename, const char* text, int FontSize, int r, int g, int b, int xpos, int ypos, SDL_Renderer* ren)
{
	font = TTF_OpenFont(filename, FontSize);
	SDL_Color TextColor = { r, g, b };
	TextSur = TTF_RenderText_Solid(font, text, TextColor);
	FontText = SDL_CreateTextureFromSurface(ren, TextSur);
	FontRect = { xpos, ypos, TextSur->w, TextSur->h };
	map[id] = FontText;
	w_store[id] = TextSur->w;
	h_store[id] = TextSur->h;
	rect_store[id] = FontRect;
	SDL_FreeSurface(TextSur);

	renderer = ren;
}

void Font::Render(string id)
{
	SDL_RenderCopy(renderer, map[id], nullptr, &rect_store[id]);
}



int Font::GetW(string id)
{
	return w_store[id];
}

int Font::GetH(string id)
{
	return h_store[id];
}
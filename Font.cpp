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

void Font::LoadFont(const char* id, const char* filename, const char* text, int FontSize, int r, int g, int b, int xpos, int ypos, SDL_Renderer* ren)
{
    if (font_store.count(id) && font_store[id]) {
        TTF_CloseFont(font_store[id]);
        font_store.erase(id);
    }

    TTF_Font* font = TTF_OpenFont(filename, FontSize);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }

    SDL_Color TextColor = { r, g, b };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, TextColor);
    if (!surface) {
        SDL_Log("Failed to render text: %s", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }
    if (map.count(id)) {
        SDL_DestroyTexture(map[id]);
        map.erase(id);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
    if (!texture) {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    SDL_Rect rect = { xpos, ypos, surface->w, surface->h };
    font_store[id] = font;
    map[id] = texture;
    w_store[id] = surface->w;
    h_store[id] = surface->h;
    rect_store[id] = rect;
    text_store[id] = text;
    color_store[id] = TextColor;

    SDL_FreeSurface(surface);
    renderer = ren;
}


void Font::Render(string id)
{
	SDL_RenderCopy(renderer, map[id], nullptr, &rect_store[id]);
}

void Font::ChangeColor(string id, int r, int g, int b)
{
    SDL_Color tmp = { r, g, b };
    color_store[id] = tmp;
    TextSur = TTF_RenderText_Solid(font_store[id], text_store[id].c_str(), color_store[id]);

    if (map.count(id)) {
        SDL_DestroyTexture(map[id]);
    }

    FontText = SDL_CreateTextureFromSurface(renderer, TextSur);
    map[id] = FontText;

    SDL_FreeSurface(TextSur);
}


int Font::GetW(string id)
{
	return w_store[id];
}

int Font::GetH(string id)
{
	return h_store[id];
}

void Font::Clean()
{
    for (auto& pair : map)
    {
        SDL_DestroyTexture(pair.second);
    }
    map.clear();
    w_store.clear();
    h_store.clear();
    rect_store.clear();
    text_store.clear();
    color_store.clear();

    for (auto& font : font_store)
    {
        TTF_CloseFont(font.second);
    }
    font_store.clear();

    renderer = nullptr;
}

#include "Font.h"

Font::Font() {}

Font::~Font() {
    CleanAll();
}

Font& Font::GetInstance() {
    static Font instance;
    return instance;
}

void Font::LoadFont(const char* id, const char* filename, const char* text, int FontSize, int r, int g, int b, int xpos, int ypos, SDL_Renderer* ren) {
    renderer = ren;
    text_store[id] = text;

    if (map.count(id)) 
    {
        SDL_DestroyTexture(map[id]);
        map.erase(id);
    }
    if (font_store.count(id)) 
    {
        TTF_CloseFont(font_store[id]);
        font_store.erase(id);
    }

    TTF_Font* font = TTF_OpenFont(filename, FontSize);
    if (!font) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return;
    }

    SDL_Color color = { r, g, b };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        SDL_Log("Failed to render text surface: %s", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
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
    color_store[id] = color;

    SDL_FreeSurface(surface);
}

void Font::Update(const char* text, string id) {
    if (!font_store.count(id) || !color_store.count(id)) return;

    if (map.count(id)) {
        SDL_DestroyTexture(map[id]);
        map.erase(id);
    }

    text_store[id] = text;

    SDL_Surface* surface = TTF_RenderText_Solid(font_store[id], text, color_store[id]);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }

    map[id] = texture;
    w_store[id] = surface->w;
    h_store[id] = surface->h;
    rect_store[id].w = surface->w;
    rect_store[id].h = surface->h;

    SDL_FreeSurface(surface);
}

void Font::Render(string id) {
    if (map.count(id)) {
        SDL_RenderCopy(renderer, map[id], nullptr, &rect_store[id]);
    }
}

void Font::ChangeColor(string id, int r, int g, int b) {
    if (!font_store.count(id) || !text_store.count(id)) return;

    SDL_Color color = { r, g, b };
    color_store[id] = color;

    SDL_Surface* surface = TTF_RenderText_Solid(font_store[id], text_store[id].c_str(), color);
    if (!surface) return;

    if (map.count(id)) {
        SDL_DestroyTexture(map[id]);
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }

    map[id] = texture;
    w_store[id] = surface->w;
    h_store[id] = surface->h;
    rect_store[id].w = surface->w;
    rect_store[id].h = surface->h;

    SDL_FreeSurface(surface);
}

int Font::GetW(string id) {
    return w_store.count(id) ? w_store[id] : 0;
}

int Font::GetH(string id) {
    return h_store.count(id) ? h_store[id] : 0;
}

void Font::Clean(string id) {
    if (map.count(id)) {
        SDL_DestroyTexture(map[id]);
        map.erase(id);
    }
    if (font_store.count(id)) {
        TTF_CloseFont(font_store[id]);
        font_store.erase(id);
    }

    w_store.erase(id);
    h_store.erase(id);
    rect_store.erase(id);
    text_store.erase(id);
    color_store.erase(id);
}

void Font::CleanAll() {
    for (auto& pair : map) {
        SDL_DestroyTexture(pair.second);
    }
    map.clear();

    for (auto& font : font_store) {
        TTF_CloseFont(font.second);
    }
    font_store.clear();

    w_store.clear();
    h_store.clear();
    rect_store.clear();
    text_store.clear();
    color_store.clear();

    renderer = nullptr;
}

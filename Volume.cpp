	#include "Volume.h"

	Volume::Volume()
	{

	}

	Volume::~Volume()
	{
		SDL_DestroyTexture(normal_thumb);
		SDL_DestroyTexture(hover_thumb);
	}

	Volume& Volume::GetInstance()
	{
		static Volume instance;
		return instance;
	}

	void Volume::LoadChanger( const char* id, int xpos, int ypos, SDL_Renderer* ren)
	{
		renderer = ren;
		normal_thumb = TextureMana::TextureLoader("assets/texture/normal_thumb.png", renderer);
		hover_thumb = TextureMana::TextureLoader("assets/texture/hover_thumb.png", renderer);
		bar = TextureMana::TextureLoader("assets/texture/bar.png", renderer);
 		x_store[id] = xpos;
		y_store[id] = ypos;
		srcrect = { 0, 0, 34, 32 };
		des_store[id] = {x_store[id] + 256  - 20, y_store[id] - 13,srcrect.w, srcrect.h};
		bar_store[id] = { x_store[id], y_store[id], 256, 8 };
	}

	void Volume::Event(const char* id, SDL_Event& event)
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		MousePoint = { mouseX, mouseY };
		if (SDL_PointInRect(&MousePoint, &des_store[id]))
		{
			is_hover[id] = true;
		}
		else
		{
			is_hover[id] = false;
		}

		if (is_hover[id] && SDL_PointInRect(&MousePoint, &des_store[id]))
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				is_pressed[id] = true;
			}
		}
		if ( event.type == SDL_MOUSEBUTTONUP)
		{
			is_pressed[id] = false;
		}
	}

	void Volume::Update(const char* id)
	{
		if (is_pressed[id])
		{
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			int offset = des_store[id].w / 2;
			int minX = bar_store[id].x;
			int maxX = bar_store[id].x + bar_store[id].w;

			mouseX = std::max(minX, std::min(mouseX, maxX));
			des_store[id].x = mouseX - offset;
		}
	}


	float Volume::Percentvolume(const char* id)
	{
		int x = des_store[id].x;
		int bar_min = bar_store[id].x;
		int bar_max = bar_store[id].x + bar_store[id].w;

		float percent = float(x - bar_min) / float(bar_max - bar_min);
		if (percent < 0.f) percent = 0.f;
		if (percent >= 1.f) percent = 1.f;

		return percent;
	}


	void Volume::Render(const char* id)
	{
		SDL_RenderCopy(renderer, bar, NULL, &bar_store[id]);
		if (is_hover[id])
		{
			SDL_RenderCopy(renderer, hover_thumb, &srcrect, &des_store[id]);
		}
		else
		{
			SDL_RenderCopy(renderer, normal_thumb, &srcrect, &des_store[id]);
		}

	}

	bool Volume::IsPressed(string id)
	{
		return is_pressed[id];
	}
#include "Animation.h"

Animation::Animation()
{

}

Animation::Animation(int Width, int Height)
{
	FrameWidth = Width;
	FrameHeight = Height;
}

Animation::~Animation()
{

}

void Animation::Define(int NumFrames)
{
	Uint32 CurrentTime = SDL_GetTicks();

	if (CurrentTime > LastFrameTime + FrameDelay)
		{
		frame = (frame + 1) % NumFrames;
		LastFrameTime = CurrentTime;
		}
}

void Animation::AniRen(SDL_Rect srcrec, SDL_Rect desrec, SDL_Renderer* ren, SDL_Texture* texture)
{
	SDL_Rect tmpsrc = srcrec;
	tmpsrc.x = frame * FrameWidth;
	SDL_RenderCopy(ren, texture, &tmpsrc, &desrec);
}

int const Animation::GetW()
{
	return FrameWidth;
}

int const Animation::GetH()
{
	return FrameHeight;
}
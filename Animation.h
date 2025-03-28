#pragma once
#include <SDL.h>

class Animation
{
public :

	Animation();
	Animation(int Width, int Height);
	~Animation();

	void Define( int NumFrames);
	void AniRen(SDL_Rect srcrec, SDL_Rect desrec, SDL_Renderer* ren, SDL_Texture * texture);
	int const GetW();
	int const GetH();
	
private:


	int FrameWidth;
	int FrameHeight;
	int frame = 0;
	int FrameDelay = 100;
	Uint32 LastFrameTime = 0;

};
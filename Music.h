#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include <unordered_map>

using namespace std;

class Music
{
public:

	static Music& GetInstance();

	~Music();

	void MusicLoader(const string& id, const char* filename);
	void SoundLoader(const string& id, const char* filename);

	void PlayMusic(const string& id, int loops = -1);
	void PlaySound(const string& id, int loops = 0);

	void StopMusic();
	void StopSound();


private:
	Music();
	unordered_map<string, Mix_Music*> music_store;
	unordered_map<string, Mix_Chunk*> sound_store;
	bool IsMuted = false;
};
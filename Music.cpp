#include "Music.h"

Music::Music()
{ }

Music::~Music()
{
	for (auto& m : music_store)
	{
		Mix_FreeMusic(m.second);
	}
	for (auto& s : sound_store)
	{
		Mix_FreeChunk(s.second);
	}
}

Music& Music::GetInstance()
{
	static Music instance;
	return instance;
}

void Music::MusicLoader(const string& id, const char* filename)
{
	Mix_Music* music = Mix_LoadMUS(filename);
	if (music)
	{
		music_store[id] = music;
	}
}

void Music::SoundLoader(const string& id, const char* filename)
{
	Mix_Chunk* sound = Mix_LoadWAV(filename);
	if (sound)
	{
		sound_store[id] = sound;
	}
}

void Music::PlayMusic(const string& id, int loops)
{
	Mix_PlayMusic(music_store[id], loops);
}

void Music::PlaySound(const string& id, int loops)
{
	Mix_PlayChannel(-1, sound_store[id], loops);
}

void Music::StopMusic()
{
	Mix_HaltMusic();
}

void Music::StopSound()
{
	Mix_HaltChannel(-1);
}
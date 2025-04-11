#include "Music.h"

Music::Music()
{ }

Music::~Music()
{
}

Music& Music::GetInstance()
{
	static Music instance;
	return instance;
}

void Music::MusicLoader(const string& id, const char* filename)
{
	if (music_store.count(id)) {
		Mix_FreeMusic(music_store[id]);
	}
	Mix_Music* music = Mix_LoadMUS(filename);
	if (music)
	{
		music_store[id] = music;
	}
}


void Music::SoundLoader(const string& id, const char* filename)
{
	if (sound_store.count(id)) {
		Mix_FreeChunk(sound_store[id]);
	}
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

void Music::MusicVolume(float percent)
{
	Mix_VolumeMusic((int) (percent * 128));
}

void Music::SoundVolume(float percent)
{
	Mix_Volume(-1, (int)(percent * 128));
}

void Music::CleanAll()
{
	for (auto& m : music_store)
	{
		Mix_FreeMusic(m.second);
	}
	music_store.clear();
	for (auto& s : sound_store)
	{
		Mix_FreeChunk(s.second);
	}
	sound_store.clear();
}

void Music::CleanMusic(const char* id)
{
	Mix_FreeMusic(music_store[id]);
	music_store.erase(id);
}


void Music::CleanSound(const char* id)
{
	Mix_FreeChunk(sound_store[id]);
	sound_store.erase(id);
}
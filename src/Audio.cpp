#include "Audio.h"

#include <iostream>
#include <exception>

Audio::Audio()
{
}

Audio::~Audio()
{
	for (auto& it : Bgm)
	{
		Mix_FreeMusic(it.second);
	}
	for (auto& it : Sound)
	{
		Mix_FreeChunk(it.second);
	}
	Mix_CloseAudio();
	Mix_Quit();
}

void Audio::Init()
{
	int ret = SDL_Init(SDL_INIT_AUDIO);
	if (ret != 0)
	{
		std::string error{ "Couldn't initialize SDL" + std::string(SDL_GetError()) };
		throw error;
	}
	ret = Mix_Init(MIX_INIT_MP3);
	if (ret != MIX_INIT_MP3)
	{
		std::string error{ "Couldn't initialize SDL" + std::string(SDL_GetError()) };
		throw error;
	}
	ret = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
	if (ret != 0)
	{
		std::string error{ "Couldn't initialize SDL" + std::string(SDL_GetError()) };
		throw error;
	}
}

void Audio::LoadAudio()
{
	Mix_VolumeMusic(5);
	Bgm["Boss2"] = Mix_LoadMUS("assets/Audio/Boss2.mp3");
	Sound["Hit"] = Mix_LoadWAV("assets/Audio/Hit.mp3");
	Mix_VolumeChunk(Sound["Hit"], 10);
	Sound["Attack"] = Mix_LoadWAV("assets/Audio/Attack.mp3");
	Mix_VolumeChunk(Sound["Attack"], 10);
	Sound["Run"] = Mix_LoadWAV("assets/Audio/Run.mp3");
	Mix_VolumeChunk(Sound["Run"], 1);
	Sound["PlayerHit"] = Mix_LoadWAV("assets/Audio/301838Preview.mp3");
	Mix_VolumeChunk(Sound["PlayerHit"], 10);
	Sound["Fire"] = Mix_LoadWAV("assets/Audio/Fire.mp3");
	Mix_VolumeChunk(Sound["Fire"], 10);
	Sound["Fire1"] = Mix_LoadWAV("assets/Audio/Fire1.mp3");
	Mix_VolumeChunk(Sound["Fire1"], 10);
}

void Audio::PlayGameBgm(const std::string_view name)
{
	Mix_FadeInMusic(Bgm[name], -1, 500);
}

void Audio::PlayGameSound(const std::string_view name)
{
	StopSound[name.data()] = Mix_PlayChannelTimed(-1, Sound[name], 0, -1);
}

void Audio::StopGameSound(const std::string& name)
{
	Mix_HaltChannel(StopSound[name]);
}

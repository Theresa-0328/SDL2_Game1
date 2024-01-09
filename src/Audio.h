#pragma once
#include <unordered_map>
#include <string>
#include <string_view>

#include <SDL.h>
#include <SDL_mixer.h>

class Audio
{
public:
	Audio();
	~Audio();
	void Init();
	void LoadAudio();
	void PlayGameBgm(const std::string_view name);
	void PlayGameSound(const std::string_view name);
	void StopGameSound(const std::string& name);
private:
	std::unordered_map<std::string_view, Mix_Music*> Bgm{};
	std::unordered_map<std::string_view, Mix_Chunk*> Sound{};
	std::unordered_map<std::string, int> StopSound{};
};
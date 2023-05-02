#pragma once
#ifndef MixerManager_h
#define MixerManager_h

#include <map>
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
class MixerManager
{
public:
    static void LoadMusic(const char* filename, std::string musicName);
    static void LoadSoundEffect(const char* filename, std::string soundName);

    static void PlayMusic(std::string musicName, int volume = 5);
    static void PlaySoundEffect(std::string soundName, int volume = 5);
    static void CleanMixer();
private:
    static std::map<std::string,Mix_Music*> musics;
    static std::map<std::string,Mix_Chunk*> chunks;
};

#endif // MixerManager_h

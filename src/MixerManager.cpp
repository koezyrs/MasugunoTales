#include "MixerManager.h"
std::map<std::string,Mix_Music*> MixerManager::musics;
std::map<std::string,Mix_Chunk*> MixerManager::chunks;

void MixerManager::LoadMusic(const char* filename, std::string musicName)
{
    Mix_Music* loadedMusic = NULL;
    loadedMusic = Mix_LoadMUS(filename);
    if(loadedMusic == NULL)
    {
        std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    musics[musicName] = loadedMusic;
}

void MixerManager::LoadSoundEffect(const char* filename, std::string soundName)
{
    Mix_Chunk* loadedSoundEffect = NULL;
    loadedSoundEffect = Mix_LoadWAV(filename);
    if(loadedSoundEffect == NULL)
    {
        std::cerr << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    chunks[soundName] = loadedSoundEffect;
}

void MixerManager::PlayMusic(std::string musicName, int volume)
{
    if(musics.count(musicName) <= 0)
    {
        std::cerr << "Can not found music: " << musicName << "!" << std::endl;
        return;
    }
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( musics[musicName], -1 );
    }else
    {
        Mix_HaltMusic();
        Mix_PlayMusic( musics[musicName], -1 );
    }
    Mix_VolumeMusic(volume);

}

void MixerManager::PlaySoundEffect(std::string soundName, int volume)
{
    if(chunks.count(soundName) <= 0)
    {
        std::cerr << "Can not found sound effect: " << soundName << "!" << std::endl;
        return;
    }
    Mix_PlayChannel( -1, chunks[soundName], 0 );
    Mix_VolumeChunk(chunks[soundName], volume);
}

void MixerManager::CleanMixer()
{
    for(auto& m : musics)
    {
        Mix_FreeMusic(m.second);
        m.second = NULL;
    }
    for(auto& se : chunks)
    {
        Mix_FreeChunk(se.second);
        se.second = NULL;
    }
}

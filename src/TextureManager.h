#pragma once

#ifndef TextureManager_h
#define TextureManager_h

#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include <string>
#include "Game.h"

class TextureManager
{
public:
    static void LoadTexture(const char* filename, std::string textureName);
    static SDL_Texture* GetTexture(std::string textureName);

    static SDL_Texture* LoadText(TTF_Font* font,const char* text, SDL_Color textColor, Uint32 wrapLength);

    static void Draw(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect);
    static void CleanTexture();
private:
    static std::map<std::string,SDL_Texture*> textures;
};



#endif // TextureManager_h

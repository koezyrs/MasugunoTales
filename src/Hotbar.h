#pragma once
#ifndef Hotbar_h
#define Hotbar_h

#include "TextureManager.h"

class Hotbar
{
public:
    Hotbar();
    ~Hotbar();
    void Update();
    void Render();
private:
    SDL_Texture* HotbarTex;
    SDL_Rect srcRect, destRect;
};

#endif // Hotbar_h

#pragma once
#ifndef SpriteComponent_h
#define SpriteComponent_h

#include <map>
#include <SDL.h>
#include "TransformComponent.h"
#include "../TextureManager.h"
#include "../Animation.h"

class SpriteComponent
{
private:
    TransformComponent* mTransform;
    SDL_Texture* mTexture;
    SDL_Rect srcRect, destRect;
    bool animated = false;
    int frames = 0;
    int speed = 100;

public:
    int animIndex = 0;
    bool isIdle = true;
    std::map<const char*, Animation> animations;

    SpriteComponent();
    SpriteComponent(std::string spriteName, TransformComponent* trans);
    SpriteComponent(std::string spriteName, TransformComponent* trans, bool isAnimated);
    ~SpriteComponent();
    void Update();
    void Render();
    void Play(const char* animName);
};

#endif // SpriteComponent_h

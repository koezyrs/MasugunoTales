#pragma once
#ifndef NameComponent_h
#define NameComponent_h

#include <string>
#include "../Game.h"
#include "TransformComponent.h"
#include "../TextureManager.h"
#include "../Vector2D.h"

class NameComponent
{
public:
    NameComponent(TransformComponent* trans, std::string _name, const char* fontPath, int fontSize, SDL_Color textColor);
    ~NameComponent();
    void Update();
    void Render();
    std::string mName;
private:
    int mWidth, mHeight;
    Vector2D position;
    SDL_Rect srcRect, destRect;
    SDL_Texture* mTexture;
    TransformComponent* mTransform;
    TTF_Font* mFont;
};

#endif // NameComponent

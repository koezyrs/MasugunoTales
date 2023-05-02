#pragma once
#ifndef Event_h
#define Event_h

#include <iostream>
#include <functional>
#include "Game.h"
#include "Component/TransformComponent.h"
#include "Component/ColliderComponent.h"
#include "Settings.h"
#include "TextureManager.h"

class Event
{
public:
    Event(float x, float y, std::string spriteName = "", std::function<void()> func = []{});
    virtual ~Event();
    void Update();
    void Render();
    void Perform();
    TransformComponent* getTransformComponent();
    ColliderComponent* getColliderComponent();
    bool isActive();
    void destroy();
private:
    bool active = true;
    Vector2D position;
    TransformComponent* mTransform;
    ColliderComponent* mCollider;
    std::function<void()> EventFunction;
    SDL_Texture* eventSprite;
    SDL_Rect srcRect, destRect;
};

#endif // Event_h

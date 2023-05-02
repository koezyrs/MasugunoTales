#pragma once

#ifndef Actor_h
#define Actor_h

#include <SDL.h>
#include <string>
#include "Game.h"
#include "Entity.h"
#include "TextureManager.h"

// Component
#include "Component/TransformComponent.h"
#include "Component/ColliderComponent.h"
#include "Component/KeyboardController.h"
#include "Component/SpriteComponent.h"
#include "Component/NameComponent.h"
#include "Component/StatsComponent.h"

#include "Vector2D.h"
#include "Settings.h"

class Actor : public Entity
{
public:
    Actor(int _actor_id, std::string characterName, int level, int exp, int next_level_exp,
          int strength, int dexterity, int intelligence, int vitality, int agility,
          int stats_used, int stats_available, float x, float y, std::string skin);
    ~Actor();
    void Update() override;
    void Render() override;
    TransformComponent* getTransformComponent();
    ColliderComponent* getColliderComponent();
    KeyboardController* getKeyboardController();
    SpriteComponent* getSpriteComponent();
    NameComponent* getNameComponent();

    StatsComponent* mStats;

    bool isActive() const;
    void destroy();
    void setPosition(float x, float y);
    int actor_id;
    void enableMovement();
    void disableMovement();
private:
    bool active = true;
    bool movement;
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    ColliderComponent* mCollider;
    KeyboardController* mController;
    NameComponent* mName;

    // Sprite Section
    SDL_Rect currentSprite;
    SDL_Rect mSpriteMoveUp[3];
    SDL_Rect mSpriteMoveDown[3];
    SDL_Rect mSpriteMoveLeft[3];
    SDL_Rect mSpriteMoveRight[3];
};

#endif // GameObject_h



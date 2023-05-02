#pragma once
#ifndef NPC_h
#define NPC_h

#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>

#include "Game.h"
#include "Entity.h"
#include "Component/TransformComponent.h"
#include "Component/ColliderComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/NameComponent.h"
#include "Dialogue.h"
#include "DialogueManager.h"

#include "Vector2D.h"


class NPC : public Entity
{
    public:
    NPC(float _x, float _y, int _width, int _height, int _scale, std::string spriteName, std::string name);
    ~NPC();
    void Update() override;
    void Render() override;
    TransformComponent* getTransformComponent();
    ColliderComponent* getColliderComponent();
    SpriteComponent* getSpriteComponent();
    NameComponent* getNameComponent();
    void PlayDialogue();
    void HideDialogue();
    bool isActive();
    void destroy();
    bool isInteract = false;
private:
    bool active = true;
    Vector2D position;
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    ColliderComponent* mCollider;
    NameComponent* mName;

    std::string npcName;
    SDL_Rect currentSprite;
    SDL_Rect mSpriteMoveUp[3];
    SDL_Rect mSpriteMoveDown[3];
    SDL_Rect mSpriteMoveLeft[3];
    SDL_Rect mSpriteMoveRight[3];
};

#endif // NPC_h

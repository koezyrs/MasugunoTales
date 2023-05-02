#pragma once
#ifndef KeyboardController_h
#define KeyboardController_h

#include <vector>
#include <cmath>

#include "../Game.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "../Entity.h"
#include "../Vector2D.h"
#include "../Database/SkillDB.h"

class Monster;

class KeyboardController
{
private:
    enum DIRECTION{
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE
    };
    Uint64 cooldownBasicAttack;
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    std::shared_ptr<Monster> target;
    DIRECTION state;
    bool *movementAvailable;
public:
    KeyboardController();
    KeyboardController(TransformComponent* trans, SpriteComponent* sprite, bool *momvement);
    std::shared_ptr<Monster> const& getTarget() const;
    void setTarget(std::shared_ptr<Monster>& _tar);
    void unsetTarget();
    void setNearestTarget();
    void PerformSkill(int skill_id, Uint64 &_cooldown, bool is_collide_monster = false);
    void Update();
};

#endif // KeyboardController_h

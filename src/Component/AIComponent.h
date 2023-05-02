#pragma once
#ifndef AIComponent_h
#define AIComponent_h

#include <cstdlib>
#include <iostream>
#include <queue>

#include <SDL.h>

#include "../Game.h"
#include "../Actor.h"
#include "../Tile.h"

#include "TransformComponent.h"

#include "../Vector2D.h"
#include "../Settings.h"

class AIComponent
{
private:
    enum STATE{
        ROAMING,
        CHASETARGET,
        RECALL
    };
    void FindTarget();
    void setTargetAndCalculateFlowField(int targetNewX, int targetNewY);
    void calculateDistances(int targetX, int targetY);
    void calculateFlowDirections();

    TransformComponent* mTransform;
    ColliderComponent* mCollider;
    Vector2D startPostion;
    bool* trigger;
    Uint64 nextAttackTime;

    float damage, attackSpeed;
    float chaseSpeed, roamSpeed;
    float attackRange, stopChaseRange;

    STATE monsterState;
    Vector2D roamPosition;
    int targetX, targetY;
    Uint64 timeout;
    std::vector<std::vector<Tile>> tiles;
    void getRandomRange(int n, int *nextMoveX, int *nextMoveY);
    bool freeze;
private:
    float lastX, lastY;
    Uint64 idleTimeout;
public:
    AIComponent(TransformComponent* trans, ColliderComponent* collider ,Vector2D startPos, float _damage, float _attackSpeed,
    float _attackRange, float _stopChaseRange, float _chaseSpeed, float _roamSpeed, bool* _trigger, std::vector<std::vector<Tile>> mapBase, bool _freeze);
    ~AIComponent();
    void Update();
    void Reset();
};

#endif // AIComponent_h

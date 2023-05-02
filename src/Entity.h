#pragma once
#ifndef Entity_h
#define Entity_h

#include "Game.h"
class Entity
{
public:
    Entity();
    virtual ~Entity();
    virtual void Update() = 0;
    virtual void Render() = 0;
};

#endif // Entity_h

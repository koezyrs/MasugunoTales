#pragma once
#ifndef Collision_h
#define Collision_h

#include <SDL.h>
#include <iostream>
#include "Component/ColliderComponent.h"

class Collision
{
public:
    static bool AABB(const SDL_Rect &rectA, const SDL_Rect &rectB); // Access Aligned Bounding Box
    static bool AABB(const ColliderComponent& colliderA, const ColliderComponent& colliderB);
};
#endif // Collision_h

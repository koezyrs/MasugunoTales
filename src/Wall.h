#pragma once
#ifndef Wall_h
#define Wall_h

#include "Vector2D.h"
#include "Entity.h"
#include "Component/TransformComponent.h"
#include "Component/ColliderComponent.h"
#include "Settings.h"

class Wall : public Entity
{
public:
    Wall(float x, float y);
    ~Wall();

    void Update() override;
    void Render() override;
    Vector2D getPosition();
    TransformComponent* getTransformComponent();
    ColliderComponent* getColliderComponent();
    bool isActive();
    void destroy();
private:
    bool active = true;
    Vector2D position;
    TransformComponent* mTransform;
    ColliderComponent* mCollider;
};
#endif // Wall_h

#pragma once
#ifndef Projectile_h
#define Projectile_h

#include "Game.h"
#include "Entity.h"
#include "Animation.h"
#include "Component/TransformComponent.h"
#include "Component/ColliderComponent.h"
#include "Vector2D.h"
#include "TextureManager.h"

class Projectile: public Entity
{
public:
    Projectile(float _x, float _y ,int _frames, int _speed, std::string _tag, std::string skillName, float _damage);
    ~Projectile();
    void Update() override;
    void Render() override;
    TransformComponent* getTransformComponent();
    ColliderComponent* getColliderComponent();
    bool isActive();
    bool isUsed();
    void Used();
    void destroy();
    std::string getTag() const;
    float getDamage();
private:
    bool active = true;
    bool used = false;
    Vector2D position;
    int frames, speed;
    SDL_Texture* mTexture;
    int Width, Height;
    SDL_Rect srcRect, destRect;
    TransformComponent* mTransform;
    ColliderComponent* mCollider;
    Uint64 startTime;
    Uint64 currentTime;
    std::string tag;
    float damage;
};

#endif // Projectile_h

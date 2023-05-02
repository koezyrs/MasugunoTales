#pragma once
#ifndef Monster_h
#define Monster_h

#include "Game.h"
#include "Actor.h"
#include "Vector2D.h"
#include "Entity.h"
#include "Component/TransformComponent.h"
#include "Component/ColliderComponent.h"
#include "Component/SpriteComponent.h"
#include "Component/AIComponent.h"
#include "Collision.h"
#include "TextureManager.h"
#include "QuestLog.h"
#include "Database/EquipmentDB.h"
#include "Database/ItemDB.h"
#include "HUD.h"
#include "Inventory.h"

class Monster : public Entity
{
public:
    Monster(int _monster_id, float _x, float _y, int _width, int _height, int _scale,  std::string _monsterName,
                 std::string _monsterSprite, float _damage, float _health, float _attackSpeed,
                 float _attackRange, float _stopChaseRange, float _chaseSpeed, float _roamSpeed, std::vector<std::vector<Tile>> mapBase,
                 int _exp_reward, int _gold_reward, int _item_reward_id, float _item_drop_percent, int _equipment_reward_id,  float _equipment_drop_percent, bool freeze = false);
    ~Monster();
    void Update() override;
    void Render() override;
    TransformComponent* getTransformComponent();
    ColliderComponent* getColliderComponent();
    SpriteComponent* getSpriteComponent();
    bool isActive() const;
    void setTrigger();
    void destroy();
    void ApplyDamage(float _damage);
    float getHP();
    float getMaxHP();
    void setTargeted();
    void unTargeted();
    bool isTargeted();
    std::string getMonsterName();
    void setPosition(float x, float y);
private:
    int monster_id;
    Vector2D startPosition;
    TransformComponent* mTransform;
    SpriteComponent* mSprite;
    ColliderComponent* mCollider;
    NameComponent* mName;
    AIComponent* mAI;

    bool active = true;
    bool trigger = false;
    bool targeted = false;

    std::string monsterName;
    std::string monsterSprite;
    float damage, health, maxhealth, attackSpeed;
    float chaseSpeed, roamSpeed;
    float attackRange, stopChaseRange;
    int exp_reward, gold_reward;
    int item_reward_id;
    float item_drop_percent;
    int equipment_reward_id;
    float equipment_drop_percent;

    SDL_Rect currentSprite;
    SDL_Rect mSpriteMoveUp[3];
    SDL_Rect mSpriteMoveDown[3];
    SDL_Rect mSpriteMoveLeft[3];
    SDL_Rect mSpriteMoveRight[3];

    // HPBar under monster
    SDL_Texture* HPBarTexture;
    SDL_Rect hpSourceRectBack, hpDestRectBack, hpSourceRectOver, hpDestRectOver;

    // Targeted icon
    SDL_Texture* targetedTexture;
    SDL_Rect targetedSrcRect, targetedDestRect;

    // Spawn time
    Uint64 timeSpawn;

private:
    void dropItem(int item_id, float x, float y);
    void dropEquipment(int equipment_id, float x, float y);
    void destroyDrop(float x, float y);
};

#endif // Monster_h

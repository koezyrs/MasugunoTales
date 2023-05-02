#include "Actor.h"

Actor::Actor(int _actor_id, std::string characterName, int level, int exp, int next_level_exp,
          int strength, int dexterity, int intelligence, int vitality, int agility,
          int stats_used, int stats_available, float x, float y, std::string skin)
: Entity::Entity(), actor_id(_actor_id), movement(true)
{
    mTransform = new TransformComponent(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, GAME_SCALE);
    mSprite = new SpriteComponent("Sprite-Player", mTransform, true);
    mCollider = new ColliderComponent(mTransform, "Player");
    mController = new KeyboardController(mTransform, mSprite, &movement);
    mName = new NameComponent(mTransform, characterName , GAME_FONT, 10, SDL_Color{0,0,0});
    mStats = new StatsComponent(level, exp, next_level_exp, strength, dexterity, intelligence, vitality, agility,
                                stats_used, stats_available);
}

Actor::~Actor()
{
    delete mController;
    delete mTransform;
    delete mCollider;
    delete mStats;
    delete mSprite;
    delete mName;
}

void Actor::Update()
{
    mController->Update();
    mTransform->Update();
    mCollider->Update();
    mStats->Update();
    mSprite->Update();
    mName->Update();
}
void Actor::Render()
{
    mSprite->Render();
    mName->Render();
}
TransformComponent* Actor::getTransformComponent()
{
    return mTransform;
}
ColliderComponent* Actor::getColliderComponent() {
    return mCollider;
}
KeyboardController* Actor::getKeyboardController() {
    return mController;
}
SpriteComponent* Actor::getSpriteComponent() {
    return mSprite;
}
NameComponent* Actor::getNameComponent() {
    return mName;
}

bool Actor::isActive() const{
    return active;
}
void Actor::destroy() {
    active = false;
}

void Actor::setPosition(float x, float y)
{
    mTransform->position = Vector2D(x,y);
}

void Actor::enableMovement()
{
    movement = true;
}
void Actor::disableMovement()
{
    movement = false;
}

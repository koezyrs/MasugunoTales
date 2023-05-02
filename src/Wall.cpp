#include "Wall.h"

Wall::Wall(float x, float y)
{
    position.x = x;
    position.y = y;
    mTransform = new TransformComponent(x, y, GAME_PIXELS, GAME_PIXELS, GAME_SCALE);
    mCollider = new ColliderComponent(mTransform, "Wall");
}

void Wall::Update()
{
    mTransform->position.x = position.x;
    mTransform->position.y = position.y;
    mCollider->Update();
}

void Wall::Render() {}
Vector2D Wall::getPosition() {return position;}
TransformComponent* Wall::getTransformComponent() {return mTransform;}
ColliderComponent* Wall::getColliderComponent() {return mCollider;}
bool Wall::isActive() {return active;}
void Wall::destroy() {active = false;}

Wall::~Wall()
{
    position.Zero();
    delete mCollider;
    delete mTransform;
}

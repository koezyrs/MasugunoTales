#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(TransformComponent* trans)
{
    mTransform = trans;
    tag = "";
    centered = false;
}

ColliderComponent::ColliderComponent(TransformComponent* trans, std::string _tag, bool isCentered)
{
    mTransform = trans;
    tag = _tag;
    centered = isCentered;
}

void ColliderComponent::Update()
{
    if(centered)
    {
        mCollider.x = static_cast<int>(mTransform->position.x + mTransform->width/4) - Game::gCamera.x;
        mCollider.y = static_cast<int>(mTransform->position.y + mTransform->height/4) - Game::gCamera.y;
        mCollider.w = mTransform->width/2 * mTransform->scale;
        mCollider.h = mTransform->height/2 * mTransform->scale;
    }else
    {
        mCollider.x = static_cast<int>(mTransform->position.x) - Game::gCamera.x;
        mCollider.y = static_cast<int>(mTransform->position.y) - Game::gCamera.y;
        mCollider.w = mTransform->width * mTransform->scale;
        mCollider.h = mTransform->height * mTransform->scale;
    }

}

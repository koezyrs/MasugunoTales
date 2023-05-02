#include "SpriteComponent.h"

SpriteComponent::SpriteComponent() {}
SpriteComponent::SpriteComponent(std::string spriteName, TransformComponent* trans)
{
    mTexture = TextureManager::GetTexture(spriteName);
    mTransform = trans;
    srcRect.x = srcRect.y = 0;
    srcRect.w = mTransform->width;
    srcRect.h = mTransform->height;
}

SpriteComponent::SpriteComponent(std::string spriteName, TransformComponent* trans, bool isAnimated)
{
    animated = isAnimated;

    Animation walkDown = Animation(0, 3, 200);
    Animation walkLeft = Animation(1, 3, 200);
    Animation walkRight = Animation(2, 3, 200);
    Animation walkUp = Animation(3, 3, 200);

    animations.emplace("Down", walkDown);
    animations.emplace("Left", walkLeft);
    animations.emplace("Right", walkRight);
    animations.emplace("Up", walkUp);

    Play("Down");

    mTexture = TextureManager::GetTexture(spriteName);
    mTransform = trans;
    srcRect.x = srcRect.y = 0;
    srcRect.w = mTransform->width;
    srcRect.h = mTransform->height;
}


SpriteComponent::~SpriteComponent()
{
    mTexture = NULL;
}

void SpriteComponent::Update()
{
    if(animated)
    {
        isIdle = false;
        if(mTransform->velocity.y == mTransform->speed && mTransform->velocity.x == 0) Play("Down");
        else if(mTransform->velocity.y < 0 && mTransform->velocity.x == 0) Play("Up");
        else if(mTransform->velocity.y == 0 && mTransform->velocity.x > 0) Play("Right");
        else if(mTransform->velocity.y == 0 && mTransform->velocity.x < 0) Play("Left");
        else if(mTransform->velocity.y > 0 && mTransform->velocity.x > 0) Play("Down");
        else if(mTransform->velocity.y > 0 && mTransform->velocity.x < 0) Play("Down");
        else if(mTransform->velocity.y < 0&& mTransform->velocity.x > 0) Play("Up");
        else if(mTransform->velocity.y < 0 && mTransform->velocity.x <0) Play("Up");
        if(mTransform->velocity == Vector2D{0.0f,0.0f}) isIdle = true;

        if(isIdle) srcRect.x = srcRect.w; // The middle animation
        else srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
    }

    srcRect.y = animIndex * mTransform->height;

    destRect.x = static_cast<int>(mTransform->position.x) - Game::gCamera.x;
    destRect.y = static_cast<int>(mTransform->position.y) - Game::gCamera.y;
    destRect.w = mTransform->width * mTransform->scale;
    destRect.h = mTransform->height * mTransform->scale;
}

void SpriteComponent::Render()
{
    TextureManager::Draw(mTexture, srcRect, destRect);
}

void SpriteComponent::Play(const char* animName)
{
    frames = animations[animName].frames;
    animIndex = animations[animName].index;
    speed = animations[animName].speed;
}

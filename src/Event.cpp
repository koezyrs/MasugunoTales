#include "Event.h"

Event::Event(float x, float y, std::string spriteName, std::function<void()> func)
:position(x,y), EventFunction([this, func]{func();}), eventSprite(NULL)
{
    mTransform = new TransformComponent(x, y, GAME_PIXELS, GAME_PIXELS, 1);
    mCollider = new ColliderComponent(mTransform, "Event");
    if(!spriteName.empty())
    {
        srcRect = {0,0,32,32};
        destRect = {static_cast<int>(x),static_cast<int>(y),32,32};
        eventSprite = TextureManager::GetTexture(spriteName);
    }
}

Event::~Event()
{
    eventSprite = NULL;
    delete mTransform;
    delete mCollider;
}

void Event::Update()
{
    mTransform->position.x = position.x;
    mTransform->position.y = position.y;
    mCollider->Update();
    if(eventSprite)
    {
        destRect.x = static_cast<int>(position.x - Game::gCamera.x);
        destRect.y = static_cast<int>(position.y - Game::gCamera.y);
    }
}

void Event::Render()
{
    if(eventSprite)
    {
        TextureManager::Draw(eventSprite, srcRect,destRect);
    }
}

TransformComponent* Event::getTransformComponent()
{
    return mTransform;
}
ColliderComponent* Event::getColliderComponent()
{
    return mCollider;
}
bool Event::isActive()
{
    return active;
}
void Event::destroy()
{
    active = false;
}
void Event::Perform()
{
    EventFunction();
}

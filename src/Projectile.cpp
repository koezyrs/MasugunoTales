#include "Projectile.h"

Projectile::Projectile(float _x, float _y ,int _frames, int _speed, std::string _tag, std::string skillSprite, float _damage)
: active(true), position(_x,_y) , frames(_frames), speed(_speed), tag(_tag), damage(_damage)
{
    mTransform = new TransformComponent(_x, _y, 64, 64, 1);
    mCollider = new ColliderComponent(mTransform, "Projectile");
    mTexture = TextureManager::GetTexture(skillSprite);
    SDL_QueryTexture(mTexture, NULL, NULL, &Width, &Height);
    srcRect = {0,0,192,192};
    destRect = {0,0,0,0};
    startTime = SDL_GetTicks64();
}

void Projectile::Update()
{
    if(srcRect.x >= Width)
    {
        destroy();
        return;
    }
    currentTime = SDL_GetTicks64() - startTime;
    mTransform->Update();
    mCollider->Update();
}
void Projectile::Render()
{
    srcRect.x = srcRect.w * static_cast<int>((currentTime / speed) % (frames + 1));
    if(srcRect.x >= Width) return;
    destRect.x = static_cast<int>(mTransform->position.x) - Game::gCamera.x;
    destRect.y = static_cast<int>(mTransform->position.y) - Game::gCamera.y;
    destRect.w = 96 * mTransform->scale;
    destRect.h = 96 * mTransform->scale;
    TextureManager::Draw(mTexture, srcRect, destRect);
}
TransformComponent* Projectile::getTransformComponent() {return mTransform;}
ColliderComponent* Projectile::getColliderComponent() {return mCollider;}
bool Projectile::isActive() {return active;}
bool Projectile::isUsed() {return used;}
void Projectile::Used() {used = true;}
void Projectile::destroy() {active = false;}
std::string Projectile::getTag() const {return tag;}
float Projectile::getDamage() {return damage;}

Projectile::~Projectile()
{
    delete mTransform;
    delete mCollider;
    mTexture = NULL;
}

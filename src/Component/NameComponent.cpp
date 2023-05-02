#include "NameComponent.h"

NameComponent::NameComponent(TransformComponent* trans, std::string _name, const char* fontPath, int fontSize, SDL_Color textColor)
{
    position.x = 0.0f;
    position.y = 0.0f;
    srcRect.x =  srcRect.y = destRect.x = destRect.y = 0;
    mTransform = trans;
    mName = _name;
    mFont = TTF_OpenFont(fontPath, fontSize);
    mTexture = TextureManager::LoadText(mFont, mName.c_str(), textColor, 200);
    SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
    srcRect.w = destRect.w = mWidth;
    srcRect.h = destRect.h = mHeight;
}
NameComponent::~NameComponent()
{
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;

    TTF_CloseFont(mFont);
    mFont = NULL;
}
void NameComponent::Update()
{
    position.x = mTransform->position.x - Game::gCamera.x;
    position.y = mTransform->position.y - 15 - Game::gCamera.y;

    destRect.x = static_cast<int>(position.x - (mWidth - mTransform->width)/2);
    destRect.y = static_cast<int>(position.y);
}
void NameComponent::Render()
{
    TextureManager::Draw(mTexture, srcRect, destRect);
}

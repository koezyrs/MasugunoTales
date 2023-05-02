#include "Hotbar.h"

Hotbar::Hotbar()
{
    HotbarTex = TextureManager::GetTexture("Hotbar");
    srcRect = {0,0,376,36};
    destRect = {324,528,376,36};
}

Hotbar::~Hotbar()
{
    HotbarTex = NULL;
}

void Hotbar::Update()
{

}

void Hotbar::Render()
{
    TextureManager::Draw(HotbarTex, srcRect,destRect);
}

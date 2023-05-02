#include "Button.h"

Button::Button(std::string spriteOut, std::string spriteOver, int x, int y, int _width, int _height, std::function<void()> func)
: position(x, y), Width(_width), Height(_height), ButtonFunction([this, func]{func();}), ButtonSpriteOut(nullptr), ButtonSpriteOver(nullptr)
{
    ButtonSpriteOut = TextureManager::GetTexture(spriteOut);
    ButtonSpriteOver = TextureManager::GetTexture(spriteOver);
    srcRect.x = srcRect.y = 0;
    destRect.x = x;
    destRect.y = y;

    srcRect.w = destRect.w = _width;
    srcRect.h = destRect.h = _height;
}

Button::~Button() {}

void Button::setPosition(int x, int y)
{
    position.x = x;
    position.y = y;
}

void Button::handleEvent(SDL_Event* e)
{
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        // check if the mouse is in the button
        if((x < position.x) || (x > position.x + Width) || (y < position.y) || (y > position.y + Height)) inside = false;
        else inside = true;

        if(inside && e->type == SDL_MOUSEBUTTONDOWN)
        {
            Perform();
        }
    }
}

void Button::Render()
{
    if(inside)
    {
        TextureManager::Draw(ButtonSpriteOver, srcRect, destRect);
    }else
    {
        TextureManager::Draw(ButtonSpriteOut, srcRect, destRect);
    }
}

void Button::Perform()
{
    ButtonFunction();
}

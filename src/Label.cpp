#include "Label.h"

Label::Label(const char* fontFile, const char* textContent, int fontSize, float x, float y, SDL_Color textColor, Uint32 wrapLength, bool isFunc , std::function<void()> func)
:  isFunctional(isFunc), position(x,y), LabelFunction([this, func]{func();}), textOut(NULL), textOver(NULL)
{
    font = TTF_OpenFont(fontFile, fontSize);
    if(textContent != NULL)
    {
        textOut = TextureManager::LoadText(font, textContent, textColor, wrapLength);
        SDL_Color textColorOver = {static_cast<int>(textColor.r) + 92, static_cast<int> (textColor.g) + 92, static_cast<int>(textColor.b) + 92};
        textOver = TextureManager::LoadText(font, textContent, textColorOver, wrapLength);
        SDL_QueryTexture(textOut, NULL, NULL, &Width, &Height);
    }else {Width = 0; Height = 0;}
    srcRect.x = srcRect.y = 0;
    destRect.x = position.x;
    destRect.y = position.y;

    srcRect.w = destRect.w = Width;
    srcRect.h = destRect.h = Height;
}

Label::~Label()
{
    Reset();
}

void Label::handleEvent(SDL_Event* e)
{
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        // check if the mouse is in the button
        if((x < position.x) || (x > position.x + Width) || (y < position.y) || (y > position.y + Height)) inside = false;
        else inside = true;

        if(inside && e->type == SDL_MOUSEBUTTONDOWN && isFunctional)
        {
            Perform();
        }

    }
}

void Label::Render()
{
    if(textOver == NULL || textOut == NULL) return;
    if(inside && isFunctional){
        TextureManager::Draw(textOver, srcRect, destRect);
    }else TextureManager::Draw(textOut, srcRect, destRect);
}

void Label::Perform()
{
    LabelFunction();
}

void Label::Reset()
{
    TTF_CloseFont(font);
    SDL_DestroyTexture(textOut);
    SDL_DestroyTexture(textOver);
    font = NULL;
    textOut = NULL;
    textOver = NULL;
}

int Label::getWidth()
{
    return Width;
}

int Label::getHeight()
{
    return Height;
}

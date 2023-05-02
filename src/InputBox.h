#pragma once
#ifndef InputBox_h
#define InputBox_h

#include <SDL.h>
#include <string>
#include "Label.h"
#include "Vector2D.h"

class InputBox
{
public:
    InputBox(float x, float y, int width, int height, int characterLimit, bool isPassword = false);
    ~InputBox();
    void setPosition(int x, int y);
    void handleEvent(SDL_Event* e);
    void Render();
    void Reset();
    void setActive();
    void deActive();
    bool isActive();
    void toogle();
    std::string inputValue;
private:
    SDL_Color White = {255,255,255};
    SDL_Color Black = {0,0,0};
    bool active = false;
    bool inside = false;
    Vector2D position;
    int Width, Height, CharacterLimit;
    bool IsPassword;
    Label* inputText;
    Label* isFocusText;
    std::string tempPassword;
};

#endif // InputBox_h

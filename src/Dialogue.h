#pragma once
#ifndef Dialogue_h
#define Dialogue_h

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Game.h"
#include "Window.h"
#include "Button.h"
#include "Label.h"
#include "TextureManager.h"

class Dialogue : public Window
{
public:
    Dialogue(int _x, int _y, int _width, int _height, const char* title, std::string facefile, const char* content);

    ~Dialogue();
    void Update() override;
    void Render() override;

    void setFace(std::string facePath);
    void setTitleLabel(const char* title);
    void setContentLabel(const char* content);
    void setOption1(const char* text, std::function<void()> func = []{});
    void setOption2(const char* text, std::function<void()> func = []{});
    void setOption3(const char* text, std::function<void()> func = []{});
    void setOption4(const char* text, std::function<void()> func = []{});
private:
    SDL_Color White = {255,255,255};
    Vector2D position;
    int mWidth, mHeight;
    SDL_Texture* DialogueBox;
    SDL_Texture* Face;
    SDL_Rect srcRect, destRect;
    SDL_Rect faceSrcRect, faceDestRect;

    Label* dialogueTitle;
    Label* dialogueContent;
    Label* dialogueOption1;
    Label* dialogueOption2;
    Label* dialogueOption3;
    Label* dialogueOption4;
    Button* closeButton;
};

#endif // Dialogue_h

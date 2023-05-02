#pragma once
#ifndef HUD_h
#define HUD_h

#include <string>

#include "Game.h"
#include "Actor.h"
#include "Monster.h"
#include "Label.h"
#include "TextureManager.h"

class HUD
{
public:
    HUD();
    ~HUD();
    void Update();
    void Render();

    void setSystemMessage(std::string _message, Uint64 timeout);
    void showGuide();
private:
    // Color
    SDL_Color White = {255,255,255};
    SDL_Color Black = {0,0,0};

    // Target
    std::shared_ptr<Monster> target;

    // GUI
    SDL_Texture* HUDBase;
    SDL_Texture* HUDBars;
    SDL_Texture* TargetHP;

    SDL_Rect BaseSrcRect, BaseDestRect;
    SDL_Rect HPSrcRect, HPDestRect;
    SDL_Rect MPSrcRect, MPDestRect;
    SDL_Rect TargetHPSrcRectBack, TargetHPDestRectBack, TargetHPSrcRectOver, TargetHPDestRectOver;

    // Player label UI
    Label* playerName;
    Label* playerLevel;
    Label* playerExperience;
    Label* playerHP;
    Label* playerMP;

    // Target label UI
    Label* targetName;
    Label* targetHP;

    // System label message
    Label* systemMessage;
    Uint64 systemMessageTimeout;

    // System Button
    Button *inventoryBtn, *ccBtn;


    // New player guide
    int guide = 0;
    Button *closePlayerGuide;
    Label* toPage2, *toPage1, *finish;
    SDL_Texture *page1, *page2;
};

#endif // HUD_h

#pragma once
#ifndef Ranking_h
#define Ranking_h

#include "Game.h"
#include "Window.h"
#include "Button.h"
#include "Label.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "Settings.h"

class Ranking : public Window
{
public:
    Ranking(int _x, int _y, int _width, int _height, std::vector<std::string> _topPower, std::vector<std::string> _topGold, std::vector<std::string> _topLevel);
    ~Ranking();
    void Update() override;
    void Render() override;
private:
    enum RANK_FIELD
    {
        POWER,
        GOLD,
        LEVEL
    };
    SDL_Color Black = {0,0,0};
    Vector2D position;
    int mWidth, mHeight;
    std::vector<Label*> topPower;
    std::vector<Label*> topGold;
    std::vector<Label*> topLevel;
    RANK_FIELD field;
    SDL_Texture* RankingBoard;
    SDL_Rect srcRect, destRect;
    Button *powerBtn, *goldBtn, *levelBtn, *closeButton;
    Label *fieldLb;
};

#endif // Ranking_h

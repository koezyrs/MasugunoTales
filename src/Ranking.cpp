#include "Ranking.h"

Ranking::Ranking(int _x, int _y, int _width, int _height, std::vector<std::string> _topPower, std::vector<std::string> _topGold, std::vector<std::string> _topLevel)
: Window::Window(), position(_x, _y), mWidth(_width), mHeight(_height), field(POWER)
{
    RankingBoard = TextureManager::GetTexture("Ranking");
    closeButton = new Button("CloseButtonOut", "CloseButtonOver", _x + 300, _y + 4, 13, 13, [this]{Window::hideWindow(); });
    powerBtn = new Button("PowerButtonOut", "PowerButtonOver", _x + 60, _y + 33, 56, 21, [this]{
                          field = POWER;
                          fieldLb->Reset();
                          fieldLb = new Label(GAME_FONT, "Total Power", 10, position.x + 208, position.y + 63, Black, 250);
                          });
    goldBtn = new Button("GoldButtonOut", "GoldButtonOver", _x + 130, _y + 33, 56, 21, [this]{
                         field = GOLD;
                         fieldLb->Reset();
                         fieldLb = new Label(GAME_FONT, "Total Gold", 10, position.x + 208, position.y + 63, Black, 250);
                         });
    levelBtn = new Button("LevelButtonOut", "LevelButtonOver", _x + 202, _y + 33, 56, 21, [this]{
                          field = LEVEL;
                          fieldLb->Reset();
                          fieldLb = new Label(GAME_FONT, "Level", 10, position.x + 208, position.y + 63, Black, 250);
                          });
    fieldLb = new Label(GAME_FONT, "Total Power", 10, _x + 208, _y + 63, Black, 250);
    srcRect = {0,0,_width,_height};
    destRect = {_x,_y,_width,_height};
    int vecSize;

    vecSize = _topPower.size();
    if(vecSize > MAX_RANKING_TOP*2) vecSize = MAX_RANKING_TOP*2;
    for(int i = 0; i < vecSize; i+= 2)
    {
        int xPos = _x + 45;
        int yPos = _y + 80 + (i/2)*27;
        topPower.push_back(new Label(GAME_FONT, _topPower[i].c_str(), 10, xPos, yPos, Black, 250));
        topPower.push_back(new Label(GAME_FONT, _topPower[i+1].c_str(), 10, xPos + 165, yPos, Black, 250));
    }

    vecSize = _topGold.size();
    if(vecSize > MAX_RANKING_TOP*2) vecSize = MAX_RANKING_TOP*2;
    for(int i = 0; i < vecSize; i+= 2)
    {
        int xPos = _x + 45;
        int yPos = _y + 80 + (i/2)*27;
        topGold.push_back(new Label(GAME_FONT, _topGold[i].c_str(), 10, xPos, yPos, Black, 250));
        topGold.push_back(new Label(GAME_FONT, _topGold[i+1].c_str(), 10, xPos + 165, yPos, Black, 250));
    }

    vecSize = _topLevel.size();
    if(vecSize > MAX_RANKING_TOP*2) vecSize = MAX_RANKING_TOP*2;
    for(int i = 0; i < vecSize; i+= 2)
    {
        int xPos = _x + 45;
        int yPos = _y + 80 + (i/2)*27;
        topLevel.push_back(new Label(GAME_FONT, _topLevel[i].c_str(), 10, xPos, yPos, Black, 250));
        topLevel.push_back(new Label(GAME_FONT, _topLevel[i+1].c_str(), 10, xPos + 165, yPos, Black, 250));
    }
}

Ranking::~Ranking()
{
    for(auto& t: topPower) delete t;
    for(auto& t: topGold) delete t;
    for(auto& t: topLevel) delete t;
}


void Ranking::Update()
{
    if(isHide()) return;
    closeButton->handleEvent(&Game::event);
    powerBtn->handleEvent(&Game::event);
    goldBtn->handleEvent(&Game::event);
    levelBtn->handleEvent(&Game::event);
}

void Ranking::Render()
{
    if(isHide()) return;
    TextureManager::Draw(RankingBoard, srcRect, destRect);
    closeButton->Render();
    powerBtn->Render();
    goldBtn->Render();
    levelBtn->Render();
    fieldLb->Render();
    SDL_Rect optionSrc = {0,0,56,21};
    switch(field)
    {
    case POWER:
        {
            SDL_Rect optionDest = {static_cast<int>(position.x) + 60, static_cast<int>(position.y) + 33, 56, 21};
            TextureManager::Draw(TextureManager::GetTexture("PowerButtonOver"), optionSrc, optionDest);
            for(auto& t: topPower) t->Render();
        }
        break;
    case GOLD:
        {
            SDL_Rect optionDest = {static_cast<int>(position.x) + 130, static_cast<int>(position.y) + 33, 56, 21};
            TextureManager::Draw(TextureManager::GetTexture("GoldButtonOver"), optionSrc, optionDest);
            for(auto& t: topGold) t->Render();
        }
        break;
    case LEVEL:
        {
            SDL_Rect optionDest = {static_cast<int>(position.x) + 202, static_cast<int>(position.y) + 33, 56, 21};
            TextureManager::Draw(TextureManager::GetTexture("LevelButtonOver"), optionSrc, optionDest);
            for(auto& t: topLevel) t->Render();
        }
        break;
    }
}

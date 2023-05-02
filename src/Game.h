#pragma once
#ifndef Game_h
#define Game_h

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <windows.h>
#include <mysql.h>
#include <memory>
#include <vector>
#include <string>
#include "Settings.h"

class Login;
class Register;
class Map;
class Actor;
class Dialogue;
class Inventory;
class CharacterInformation;
class HUD;
class Hotbar;
class QuestLog;
class Shop;
class Ranking;

using namespace std;

enum SESSION_GAME
    {
        INIT,
        LOAD_RESOURCES,
        LOAD_MIX,
        LOGIN,
        REGISTER,
        LOAD_DATA,
        RUNNING,
        SAVE_DATA,
        CLEAR
    };

class Game{
public:
    Game();
    ~Game();
    void init(const char* titile, int xpos, int ypos, int width, int height);
    void loadResources();
    void loadMix();
    void loginProcess();
    void registProcess();
    void loadData();
    void handleEvents();
    void update();
    void render();
    void saveData();
    void clean();

    static SDL_Event event;
    static SDL_Renderer* gRenderer;
    static MYSQL* conn;
    static std::shared_ptr<Map> currentMap;
    static std::unique_ptr<Actor> gPlayer;
    static std::unique_ptr<Dialogue> gDialogue;
    static std::unique_ptr<Inventory> gInventory;
    static std::unique_ptr<CharacterInformation> gCharacterInformation;
    static std::unique_ptr<HUD> gHUD;
    static std::unique_ptr<Hotbar> gHotbar;
    static std::unique_ptr<QuestLog> gQuestLog;
    static std::unique_ptr<Shop> gShop;
    static std::unique_ptr<Ranking> gRanking;

    static SDL_Rect gCamera;
    static SESSION_GAME session;
private:
    SDL_Window* gWindow;
    Login* loginPanel;
    Register* registerPanel;

};
#endif // Game_h

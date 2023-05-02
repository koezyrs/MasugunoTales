#pragma once

#ifndef Map_h
#define Map_h

#include <string>
#include <fstream>
#include <vector>
#include <functional>
#include <memory>
#include <algorithm>
#include <iostream>
#include <queue>
#include <iomanip>

#include "Game.h"
#include "Actor.h"
#include "Monster.h"
#include "NPC.h"
#include "Wall.h"
#include "Projectile.h"
#include "Event.h"
#include "Tile.h"

#include "Vector2D.h"
#include "TextureManager.h"
#include "Settings.h"

// Database
#include "Database/MonsterDB.h"

class Map
{
public:
    Map(int _id, std::string maptex, std::string overlay);
    ~Map();
    int id;
    void AddWall(float x, float y);
    void AddMonster(float x, float y, int monster_id, std::vector<std::vector<Tile>> mapBase);
    void AddEvent(float x, float y, std::string spriteName = "", std::function<void()> func = []{});
    void AddNPC(float x, float y, const char* filepath, std::string name);
    void AddProjectile(float x, float y, int frames, std::string skillName, float _damage);
    int getWidth();
    int getHeight();
    int getSizeX();
    int getSizeY();
    void ClearMap();
    void Refresh();
    void Update();
    void RenderBottomLayer();
    void RenderUpperLayer();
    std::vector<std::shared_ptr<Event>> events;
    std::vector<std::shared_ptr<Wall>> walls;
    std::vector<std::shared_ptr<Monster>> monsters;
    std::vector<std::shared_ptr<NPC>> npcs;
    std::vector<std::shared_ptr<Projectile>> projectiles;
private:
    int width;
    int height;
    int sizeX;
    int sizeY;
    int targetX;
    int targetY;
    Vector2D position;
    SDL_Texture* mTexture;
    SDL_Texture* mTexture_Overlay;
    SDL_Rect srcRect, destRect;
};

#endif // Map_h

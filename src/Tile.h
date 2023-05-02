#pragma once
#ifndef Tile_h
#define Tile_h

#include "Vector2D.h"
#include "Settings.h"

class Tile
{
public:
    Tile();
    Tile(float x, float y, bool _isWall);
    ~Tile();
    Vector2D position;
    int flowDirectionX;
    int flowDirectionY;
    unsigned int flowDistance;
    bool isWall;
};

#endif // Tile_h

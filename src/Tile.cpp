#include "Tile.h"
Tile::Tile() {}
Tile::Tile(float x, float y, bool _isWall)
: position(x,y), flowDirectionX(0), flowDirectionY(0), flowDistance(flowDistanceMax), isWall(_isWall) {}
Tile::~Tile() {}

#pragma once

#ifndef TransformComponent_h
#define TransformComponent_h

#include "../Vector2D.h"
#include "../Settings.h"

class TransformComponent
{
public:
    Vector2D position;
    Vector2D velocity;
    int width = GAME_PIXELS;
    int height = GAME_PIXELS;
    int scale = 1;
    float speed = 2;

    TransformComponent();
    TransformComponent(int _scale);
    TransformComponent(float _x, float _y);
    TransformComponent(float _x, float _y, int _width, int _height, int _scale);

    ~TransformComponent();
    void Update();
};

#endif // TransformComponent_h

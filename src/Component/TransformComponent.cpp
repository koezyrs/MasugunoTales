#include "TransformComponent.h"

TransformComponent::TransformComponent()
{
    position.Zero();
    velocity.Zero();
}

TransformComponent::TransformComponent(int _scale)
{
    position.Zero();
    velocity.Zero();
    scale = _scale;
}

TransformComponent::TransformComponent(float _x, float _y)
{
    position.x = _x;
    position.y = _y;
    velocity.Zero();
}

TransformComponent::TransformComponent(float _x, float _y, int _width, int _height, int _scale)
{
    position.x = _x;
    position.y = _y;
    width = _width;
    height = _height;
    scale = _scale;
    velocity.Zero();
}

TransformComponent::~TransformComponent()
{
    position.Zero();
    velocity.Zero();
    width = height = scale = speed = 0;
}
void TransformComponent::Update()
{
    position.x += velocity.x;
    position.y += velocity.y;
}

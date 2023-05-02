#include <cmath>
#include "Vector2D.h"

Vector2D::Vector2D()
{
    x = 0.0f;
    y = 0.0f;
}

Vector2D::Vector2D(float _x, float _y)
{
    this->x = _x;
    this->y = _y;
}

Vector2D& Vector2D::Add(const Vector2D& vec)
{
    this->x += vec.x;
    this->y += vec.y;
    return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
    this->x -= vec.x;
    this->y -= vec.y;
    return *this;
}
Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
    this->x *= vec.x;
    this->y *= vec.y;
    return *this;
}
Vector2D& Vector2D::Divide(const Vector2D& vec)
{
    this->x /= vec.x;
    this->y /= vec.y;
    return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
    return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
    return v1.Subtract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
    return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
    return v1.Divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
    return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
    return this->Subtract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
    return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
    return this->Divide(vec);
}

Vector2D& Vector2D::operator*(const float& i)
{
    this->x *= i;
    this->y *= i;
    return *this;
}

Vector2D& Vector2D::Zero()
{
    this->x = 0;
    this->y = 0;
    return *this;
}

bool Vector2D::operator==(const Vector2D& vec)
{
    if((this->x == vec.x) && (this->y == vec.y)) return true;
    return false;
}

bool Vector2D::operator!=(const Vector2D& vec)
{
    if((this->x != vec.x) || (this->y != vec.y)) return true;
    return false;
}

float Vector2D::DistanceTo(const Vector2D& vec)
{
    return sqrt((this->x - vec.x)*(this->x - vec.x) + (this->y - vec.y)*(this->y - vec.y));
}

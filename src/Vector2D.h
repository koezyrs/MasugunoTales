#pragma once
#ifndef Vector2D_h
#define Vector2D_h

class Vector2D
{
public:
    float x;
    float y;

    Vector2D();
    Vector2D(float _x, float _y);

    Vector2D& Add(const Vector2D& vec);
    Vector2D& Subtract(const Vector2D& vec);
    Vector2D& Multiply(const Vector2D& vec);
    Vector2D& Divide(const Vector2D& vec);

    friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

    Vector2D& operator+=(const Vector2D& vec);
    Vector2D& operator-=(const Vector2D& vec);
    Vector2D& operator*=(const Vector2D& vec);
    Vector2D& operator/=(const Vector2D& vec);

    Vector2D& operator*(const float& i);
    Vector2D& Zero();

    bool operator==(const Vector2D& vec);
    bool operator!=(const Vector2D& vec);

    float DistanceTo(const Vector2D& vec);
};

#endif // Vector2D_h

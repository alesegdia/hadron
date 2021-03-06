#pragma once

namespace hadron {


static const float HADRON_EPSILON = 0.000000001f;

struct Vec2
{
    Vec2(){}
    Vec2(float x_, float y_) : x(x_), y(y_) {}
    float x = 0;
    float y = 0;

    Vec2& operator=( const Vec2& other )
    {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }


};

bool operator==( const Vec2& a, const Vec2& b );

bool operator!=( const Vec2& a, const Vec2& b );


}



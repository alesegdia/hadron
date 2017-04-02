#pragma once

namespace hadron {


namespace math
{

static const float HDRN_ZERO_THRESHOLD = 0.001f;

struct Vec2
{
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

}



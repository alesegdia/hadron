#pragma once

#include "vec.h"

namespace hadron {

struct CollisionInfo
{
    bool left;
    bool top;
    bool collides;
};

struct AABB
{
    static CollisionInfo CheckCollision( const AABB& b1, const AABB& b2 )
    {
        bool c = Collides(b1, b2);
        CollisionInfo ci;
        if( c )
        {
            ci = ComputeOrientation(b1, b2);
        }
        ci.collides = c;
        return ci;
    }
    static bool Collides(const AABB& b1, const AABB& b2);
    
    static CollisionInfo ComputeOrientation(const AABB& b1, const AABB& b2);

    AABB() : x(0), y(0), width(0), height(0) {}
    AABB(float x_, float y_, float w_, float h_)
        : x(x_), y(y_), width(w_), height(h_) {}
    float x, y, width, height;
};


}

#pragma once

#include "vec.h"

namespace hadron {

struct AABB
{
    static bool collides(const AABB& b1, const AABB& b2);

    AABB() : x(0), y(0), width(0), height(0) {}
    AABB(float x_, float y_, float w_, float h_)
        : x(x_), y(y_), width(w_), height(h_) {}
    float x, y, width, height;
};


}

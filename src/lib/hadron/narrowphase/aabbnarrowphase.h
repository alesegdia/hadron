#pragma once

#include "narrowphase.h"
#include "../body.h"

namespace hadron {
namespace collision {

class AABBNarrowphase
{
public:
    virtual ~AABBNarrowphase()
    {

    }

    bool resolve(Body& b1, Body& b2)
    {
        return AABB::collides(b1.aabb(), b2.aabb());
    }
};

}
}

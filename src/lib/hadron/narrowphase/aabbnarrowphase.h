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

    CollisionInfo resolve(const Body& b1, const Body& b2) const
    {
        return AABB::checkCollision(b1.aabb(), b2.aabb());
    }
};

}
}

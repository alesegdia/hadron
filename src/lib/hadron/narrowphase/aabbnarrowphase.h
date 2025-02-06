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

    CollisionInfo Resolve(const Body& b1, const Body& b2) const
    {
        return AABB::CheckCollision(b1.GetLocalAABB(), b2.GetLocalAABB());
    }
};

}
}

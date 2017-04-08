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

    bool resolve( const Body& b1, const Body& b2 ) const
    {
        return AABB::collides(b1.aabb(), b2.aabb());
    }
};

}
}

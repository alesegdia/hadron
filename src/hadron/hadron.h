#pragma once

#include <vector>
#include <algorithm>

#include "math.h"
#include "util.h"
#include "body.h"
#include "broadphase.h"
#include "narrowphase.h"
#include "world.h"


namespace hadron {



namespace collision
{



/**
 * We care about CollisionListener memory management only if it's registered on shutdown
 */
class ICollisionListener {

public:

    virtual ~ICollisionListener() = 0 ;

    /**
     * @brief collisionHappened
     * @param b1
     * @param b2
     */
    virtual void collisionHappened( const Body& b1, const Body& b2 ) = 0;

};


}

}

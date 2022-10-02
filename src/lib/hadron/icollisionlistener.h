#pragma once

#include "body.h"

namespace hadron {


struct CollisionResult {
    const Body* b1;
    const Body* b2;
    CollisionInfo colinfo;
};


class ICollisionListener {

public:

    virtual ~ICollisionListener() = 0 ;

    virtual void OnCollisionEnter( Body& b1, Body& b2, CollisionResult cr );

    virtual void OnCollisionStay( Body& b1, Body& b2 );

    virtual void OnCollisionExit( Body& b1, Body& b2 );

};


}

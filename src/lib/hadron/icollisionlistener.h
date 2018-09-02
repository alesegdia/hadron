#pragma once

#include "body.h"

namespace hadron {


class ICollisionListener {

public:

    virtual ~ICollisionListener() = 0 ;

    virtual void onCollisionEnter( Body& b1, Body& b2 );

    virtual void onCollision( Body& b1, Body& b2 );

    virtual void onCollisionExit( Body& b1, Body& b2 );

};


}

#include "icollisionlistener.h"

namespace hadron {


ICollisionListener::~ICollisionListener() = default;

void ICollisionListener::onCollisionEnter(Body &b1, Body &b2, CollisionResult result)
{
    (void)b1;
    (void)b2;
}

void ICollisionListener::onCollision(Body &b1, Body &b2)
{
    (void)b1;
    (void)b2;
}

void ICollisionListener::onCollisionExit(Body &b1, Body &b2)
{
    (void)b1;
    (void)b2;
}


}

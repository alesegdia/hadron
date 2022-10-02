#include "icollisionlistener.h"

namespace hadron {


ICollisionListener::~ICollisionListener() = default;

void ICollisionListener::OnCollisionEnter(Body &b1, Body &b2, CollisionResult result)
{
    (void)b1;
    (void)b2;
}

void ICollisionListener::OnCollisionStay(Body &b1, Body &b2)
{
    (void)b1;
    (void)b2;
}

void ICollisionListener::OnCollisionExit(Body &b1, Body &b2)
{
    (void)b1;
    (void)b2;
}


}

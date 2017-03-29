#include "broadphase.h"


namespace hadron {


namespace collision
{

void Broadphase::registerListener(ICollisionListener *listener)
{
    m_collisionListeners.push_back(listener);
}

void Broadphase::unregisterListener(ICollisionListener *listener)
{
    util::remove_by_value( m_collisionListeners, listener );
}

void Broadphase::collisionHappened(const Body &b1, const Body &b2)
{
    for( auto listener : m_collisionListeners )
    {
        listener->collisionHappened( b1, b2 );
    }
}

}

}

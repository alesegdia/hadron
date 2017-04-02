#include "broadphase.h"
#include "util.h"

namespace hadron {


namespace collision
{

ICollisionListener::~ICollisionListener() {

}

void Broadphase::registerListener(ICollisionListener *listener)
{
    m_collisionListeners.push_back(listener);
}

void Broadphase::unregisterListener(ICollisionListener *listener)
{
    util::remove_by_value<ICollisionListener*>( m_collisionListeners, listener );
}

void Broadphase::collisionHappened(const Body &b1, const Body &b2)
{
    for( auto listener : m_collisionListeners )
    {
        listener->collisionHappened( b1, b2 );
    }
}

BruteForceBroadphase::BruteForceBroadphase()
{

}

BruteForceBroadphase::~BruteForceBroadphase()
{
    for( auto body : m_bodies )
    {
        delete body;
    }
}

void BruteForceBroadphase::step()
{
    for( int idb1 = 0; idb1 < m_bodies.size(); idb1++ )
    {
        for( int idb2 = idb1 + 1; idb2 < m_bodies.size(); idb2++ )
        {
            const Body& b1 = *m_bodies[idb1];
            const Body& b2 = *m_bodies[idb2];

            if( true == Body::collides( b1, b2 ) )
            {
                collisionHappened( b1, b2 );
            }
        }
    }
}

void BruteForceBroadphase::registerBody(Body::Ptr body)
{
    m_bodies.push_back( body );
    //return *m_bodies.end();
}

void BruteForceBroadphase::unregisterBody(Body::Ptr body)
{
    util::remove_by_value<Body::Ptr>(m_bodies, body);
}


}

}

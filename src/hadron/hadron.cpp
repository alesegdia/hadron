
#include "./hadron.h"

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


ICollisionListener::~ICollisionListener() {

}

IBodyObserver::~IBodyObserver() {

}

void DirtyBodyCollector::onBodyInserted(Body *b)
{
    m_bodies.push_back(b);
}

void DirtyBodyCollector::onBodyRemoved(Body *b)
{
    util::remove_by_value( m_bodies, b );
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

void BruteForceBroadphase::registerBody(Body *body)
{
    m_bodies.push_back( body );
    //return *m_bodies.end();
}

void BruteForceBroadphase::unregisterBody(Body *body)
{
    m_bodies.erase( std::remove( m_bodies.begin(), m_bodies.end(), body ), m_bodies.end() );
}

}

}

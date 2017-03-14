
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

void Broadphase::collisionHappened(const Body &b1, const Body &b2) {
    for( auto listener : m_collisionListeners )
    {
        listener->collisionHappened( b1, b2 );
    }
}

bool Body::collides(const Body &rect1, const Body &rect2)
{
    if ( rect1.x() < rect2.x() + rect2.width()  &&
         rect1.x() + rect1.width() > rect2.x()  &&
         rect1.y() < rect2.y() + rect2.height() &&
         rect1.height() + rect1.y() > rect2.y() )
    {
        return true;
    }

}

const void *Body::userData() const {
    return m_userdata;
}

void Body::userData(void *userData) {
    m_userdata = userData;
}

bool Body::dirty()
{
    return m_dirty;
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

}

}

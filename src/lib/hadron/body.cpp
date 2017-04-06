#include "body.h"

namespace hadron {
namespace collision {

IBodyObserver::~IBodyObserver() {

}

bool Body::collides(const Body &rect1, const Body &rect2)
{
    if ( rect1.aabb().x < rect2.aabb().x + rect2.aabb().width  &&
         rect1.aabb().x + rect1.aabb().width > rect2.aabb().x  &&
         rect1.aabb().y < rect2.aabb().y + rect2.aabb().height &&
         rect1.aabb().height + rect1.aabb().y > rect2.aabb().y )
    {
        return true;
    }

}

void *Body::userData() {
    return m_userdata;
}

void Body::userData(void *userData) {
    m_userdata = userData;
}

bool Body::dirty()
{
    return m_dirty;
}


}
}

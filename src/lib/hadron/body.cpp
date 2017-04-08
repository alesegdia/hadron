#include "body.h"

namespace hadron {
namespace collision {

IBodyObserver::~IBodyObserver() {

}

bool AABB::collides(const AABB &b1, const AABB &b2)
{
    if ( b1.x < b2.x + b2.width  &&
         b1.x + b1.width > b2.x  &&
         b1.y < b2.y + b2.height &&
         b1.height + b1.y > b2.y )
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

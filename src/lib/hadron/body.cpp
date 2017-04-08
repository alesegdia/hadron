#include "body.h"

namespace hadron {
namespace collision {

IBodyObserver::~IBodyObserver() {

}

bool AABB::collides(const AABB &aabb1, const AABB &aabb2)
{
    return  aabb1.x < aabb2.x + aabb2.width  &&
            aabb1.x + aabb1.width > aabb2.x  &&
            aabb1.y < aabb2.y + aabb2.height &&
            aabb1.height + aabb1.y > aabb2.y;
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

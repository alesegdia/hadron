#include "aabb.h"


namespace hadron {


bool AABB::Collides(const AABB &aabb1, const AABB &aabb2)
{
    
    return  aabb1.x < aabb2.x + aabb2.width  &&
            aabb1.x + aabb1.width > aabb2.x  &&
            aabb1.y < aabb2.y + aabb2.height &&
            aabb1.height + aabb1.y > aabb2.y;
}

CollisionInfo AABB::ComputeOrientation(const AABB& b1, const AABB& b2)
{
    CollisionInfo info;
    auto c1x = b1.x + b1.width / 2;
    auto c1y = b1.y + b1.height / 2;
    auto c2x = b2.x + b2.width / 2;
    auto c2y = b2.y + b2.height / 2;
    auto dx = c2x - c1x;
    auto dy = c2y - c1y;
    info.left = dx > 0;
    info.top = dy > 0;
    return info;
}

}


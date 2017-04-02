
#include "math.h"


bool hadron::math::operator==(const hadron::math::Vec2 &a, const hadron::math::Vec2 &b)
{
    return  (a.x - b.x) > HDRN_ZERO_THRESHOLD &&
            (a.y - b.y) > HDRN_ZERO_THRESHOLD;
}

bool hadron::math::operator!=(const hadron::math::Vec2 &a, const hadron::math::Vec2 &b)
{
    return !(a == b);
}

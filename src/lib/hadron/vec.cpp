
#include "vec.h"


namespace hadron {


bool operator==(const Vec2 &a, const Vec2 &b)
{
    return  (a.x - b.x) > HADRON_EPSILON &&
            (a.y - b.y) > HADRON_EPSILON;
}

bool operator!=(const Vec2 &a, const Vec2 &b)
{
    return !(a == b);
}


}

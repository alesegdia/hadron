#include "body.h"

namespace hadron {
namespace collision {

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


}
}

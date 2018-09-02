#include "body.h"

namespace hadron {


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

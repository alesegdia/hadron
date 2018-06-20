#include "bruteforcebroadphase.h"

#include "../util.h"
#include "../icollisionlistener.h"

namespace hadron {


namespace collision
{



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
    for( size_t idb1 = 0; idb1 < m_bodies.size(); idb1++ )
    {
        Body& b1 = *m_bodies[idb1];
        if( b1.dirty() )
        {
            b1.clearDirty();
            for( size_t idb2 = idb1 + 1; idb2 < m_bodies.size(); idb2++ )
            {
                Body& b2 = *m_bodies[idb2];

                if( true == resolve(b1, b2) )
                {
                    collisionHappened( b1, b2 );
                }
            }
        }
    }
}

void BruteForceBroadphase::registerBody(Body::Ptr body)
{
    m_bodies.push_back( body );
    //return *m_bodies.end();
}

void BruteForceBroadphase::unregisterBody(Body::Ptr body)
{
    util::remove_by_value<Body::Ptr>(m_bodies, body);
}

void BruteForceBroadphase::visit(IBodyVisitor *visitor)
{
    for( auto body : m_bodies )
    {
        visitor->visit(body);
    }
}


}

}


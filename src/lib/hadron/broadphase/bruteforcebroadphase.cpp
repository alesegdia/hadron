#include "bruteforcebroadphase.h"

#include "../util.h"
#include "../icollisionlistener.h"

namespace hadron {


namespace collision
{



BruteForceBroadphase::BruteForceBroadphase()
= default;

BruteForceBroadphase::~BruteForceBroadphase()
{
    for( auto body : m_bodies )
    {
        delete body;
    }
}

void BruteForceBroadphase::Step()
{
    for( size_t idb1 = 0; idb1 < m_bodies.size(); idb1++ )
    {
        Body& b1 = *m_bodies[idb1];
        for( size_t idb2 = idb1 + 1; idb2 < m_bodies.size(); idb2++ )
        {
            Body& b2 = *m_bodies[idb2];

            auto result = Resolve(b1, b2);
            if( result.colinfo.collides )
            {
                CollisionHappened( b1, b2, result );
            }
        }
    }
}

void BruteForceBroadphase::RegisterBody(Body::Ptr body)
{
    m_bodies.push_back( body );
    //return *m_bodies.end();
}

void BruteForceBroadphase::UnregisterBody(Body::Ptr body)
{
    RemoveByValue<Body::Ptr>(m_bodies, body);
}

void BruteForceBroadphase::Visit(IBodyVisitor *visitor)
{
    for( auto body : m_bodies )
    {
        visitor->visit(body);
    }
}


}

}


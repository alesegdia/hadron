#pragma once

#include <vector>

#include "../body.h"

#include "../ibodyvisitor.h"
#include "../narrowphase.h"
#include "../icollisionlistener.h"
#include "../util.h"

namespace hadron {
namespace collision {

/**
 * We care about CollisionListener memory management only if it's registered on shutdown
 */


struct CollisionPairData
{
    CollisionPairData(Body::Ptr b1_, Body::Ptr b2_) : b1(b1_), b2(b2_) {}
    Body::Ptr b1, b2;
};

template <typename NarrowphaseType>
class Broadphase {
public:

    virtual ~Broadphase() {

    }

    /*
    void update()
    {
        // We remove onCollision because it is manageable by the user outside, so we can reduce our scope
        for( auto& collision : m_collisions )
        {
            dispatchCollisionEvent(collision, Broadphase::emitCollision);
        }
    }
    */

    typedef int (Broadphase::*Method)(ICollisionListener* listener, CollisionPairData&);

    void emitCollisionEnter(ICollisionListener* listener, CollisionPairData& collision)
    {
        listener->onCollisionEnter( *collision.b1, *collision.b2 );
    }

    /*
    void emitCollision(ICollisionListener* listener, CollisionPairData& collision)
    {
        listener->onCollision( *collision.b1, *collision.b2 );
    }
    */

    void emitCollisionExit(ICollisionListener* listener, CollisionPairData& collision)
    {
        listener->onCollisionExit( *collision.b1, *collision.b2 );
    }


    void dispatchCollisionEvent(CollisionPairData& collision, Method m)
    {
        for( CollisionPairData& collision : m_collisions )
        {
            for( auto listener : m_collisionListeners ) {
                (this->*m(listener, collision));
            }
        }
    }

    virtual void step() = 0;

    virtual void registerBody( Body::Ptr body ) = 0 ;
    virtual void unregisterBody( Body::Ptr body ) = 0 ;

    virtual void visit(IBodyVisitor* visitor) = 0 ;

    void registerListener( ICollisionListener* listener )
    {
        m_collisionListeners.push_back(listener);
    }
    void unregisterListener( ICollisionListener* listener )
    {
        util::remove_by_value<ICollisionListener*>( m_collisionListeners, listener );
    }

protected:
    void collisionHappened( Body& b1, Body& b2 )
    {
        m_collisions.push_back(CollisionPairData(&b1, &b2));
        for( auto listener : m_collisionListeners )
        {
            listener->onCollisionEnter( b1, b2 );
        }
    }

private:
    std::vector<ICollisionListener*> m_collisionListeners;
    NarrowphaseType m_narrowphase;
    std::vector<CollisionPairData> m_collisions;

};


}
}

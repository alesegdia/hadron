#pragma once

#include <vector>

#include "../body.h"

#include "../ibodyvisitor.h"
#include "../narrowphase/narrowphase.h"
#include "../icollisionlistener.h"
#include "../util.h"

namespace hadron {
namespace collision {

/**
 * We care about CollisionListener memory management only if it's registered on shutdown
 */


struct CollisionPairData
{
    CollisionPairData(Body& b1_, Body& b2_) : b1(b1_), b2(b2_) {}
    Body& b1;
    Body& b2;
};

template <typename NarrowphaseType>
class Broadphase {
public:

    virtual ~Broadphase() {

    }

    virtual std::vector<Body*>&& queryAABB( const AABB& aabb ) = 0 ;

    typedef void (Broadphase::*Method)(ICollisionListener*, Body&, Body&);

    void emitCollisionEnter(ICollisionListener* listener, Body& b1, Body& b2)
    {
        listener->onCollisionEnter( b1, b2 );
    }

    void emitCollisionExit(ICollisionListener* listener, Body& b1, Body& b2)
    {
        listener->onCollisionExit( b1, b2 );
    }

    void dispatchCollisionEvent(Method m, Body& b1, Body& b2)
    {
        for( auto listener : m_collisionListeners ) {
            (this->*m)(listener, b1, b2);
        }
    }

    void update()
    {
        collisionStep();
        step();
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

    void collisionStep()
    {
        for( CollisionPairData& cpd : m_collisions )
        {
            if( cpd.b1.dirty() || cpd.b2.dirty() )
            {
                bool collided = resolve(cpd.b1, cpd.b2);
                if( !collided )
                {
                    dispatchCollisionEvent(&Broadphase::emitCollisionExit, cpd.b1, cpd.b2);
                }
            }
        }
    }

protected:
    void collisionHappened( Body& b1, Body& b2 )
    {
        m_collisions.push_back(CollisionPairData(b1, b2));
        dispatchCollisionEvent(&Broadphase::emitCollisionEnter, b1, b2);
        for( auto listener : m_collisionListeners )
        {
            listener->onCollisionEnter( b1, b2 );
        }
    }

    bool resolve( const Body& b1, const Body& b2 ) const
    {
        return narrowphase().resolve(b1, b2);
    }

    const NarrowphaseType& narrowphase() const
    {
        return m_narrowphase;
    }

private:
    std::vector<ICollisionListener*> m_collisionListeners;
    NarrowphaseType m_narrowphase;
    std::vector<CollisionPairData> m_collisions;

};


}
}

#pragma once

#include <vector>

#include "../body.h"

#include "../ibodyvisitor.h"
#include "../narrowphase/narrowphase.h"
#include "../icollisionlistener.h"
#include "../util.h"

namespace hadron {

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

    virtual std::vector<Body*> queryAABB( const AABB& aabb ) = 0 ;

    typedef void (Broadphase::*Method)(ICollisionListener*, Body&, Body&);
    typedef void (Broadphase::*Method2)(ICollisionListener*, Body&, Body&, CollisionResult);

    void emitCollisionEnter(ICollisionListener* listener, Body& b1, Body& b2, CollisionResult cr)
    {
        listener->onCollisionEnter( b1, b2, cr );
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

    void dispatchCollisionEvent(Method2 m, Body& b1, Body& b2, CollisionResult cr)
    {
        for( auto listener : m_collisionListeners ) {
            (this->*m)(listener, b1, b2, cr);
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
        remove_by_value<ICollisionListener*>( m_collisionListeners, listener );
    }

    void collisionStep()
    {
        for( CollisionPairData& cpd : m_collisions )
        {
            if( cpd.b1.dirty() || cpd.b2.dirty() )
            {
                auto result = resolve(cpd.b1, cpd.b2);
                if( !result.colinfo.collides )
                {
                    dispatchCollisionEvent(&Broadphase::emitCollisionExit, cpd.b1, cpd.b2);
                }
            }
        }
    }

protected:
    void collisionHappened( Body& b1, Body& b2, CollisionResult cr )
    {
        m_collisions.push_back(CollisionPairData(b1, b2));
        dispatchCollisionEvent(&Broadphase::emitCollisionEnter, b1, b2, cr);
    }
    
    CollisionResult resolve( const Body& b1, const Body& b2 ) const
    {
        CollisionResult cr;
        cr.colinfo = narrowphase().resolve(b1, b2);
        cr.b1 = &b1;
        cr.b2 = &b2;
        return cr;
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

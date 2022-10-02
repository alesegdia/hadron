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

    virtual std::vector<Body*> QueryAABB( const AABB& aabb ) = 0 ;

    typedef void (Broadphase::*Method)(ICollisionListener*, Body&, Body&);
    typedef void (Broadphase::*Method2)(ICollisionListener*, Body&, Body&, CollisionResult);

    void EmitCollisionEnter(ICollisionListener* listener, Body& b1, Body& b2, CollisionResult cr)
    {
        listener->OnCollisionEnter( b1, b2, cr );
    }

    void EmitCollisionExit(ICollisionListener* listener, Body& b1, Body& b2)
    {
        listener->OnCollisionExit( b1, b2 );
    }

    void DispatchCollisionEvent(Method m, Body& b1, Body& b2)
    {
        for( auto listener : m_collisionListeners ) {
            (this->*m)(listener, b1, b2);
        }
    }

    void DispatchCollisionEvent(Method2 m, Body& b1, Body& b2, CollisionResult cr)
    {
        for( auto listener : m_collisionListeners ) {
            (this->*m)(listener, b1, b2, cr);
        }
    }

    void Update()
    {
        CollisionStep();
        Step();
    }

    virtual void Step() = 0;

    virtual void RegisterBody( Body::Ptr body ) = 0 ;
    virtual void UnregisterBody( Body::Ptr body ) = 0 ;

    virtual void Visit(IBodyVisitor* visitor) = 0 ;

    void RegisterListener( ICollisionListener* listener )
    {
        m_collisionListeners.push_back(listener);
    }
    void UnregisterListener( ICollisionListener* listener )
    {
        RemoveByValue<ICollisionListener*>( m_collisionListeners, listener );
    }

    void CollisionStep()
    {
        for( CollisionPairData& cpd : m_collisions )
        {
            if( cpd.b1.IsDirty() || cpd.b2.IsDirty() )
            {
                auto result = Resolve(cpd.b1, cpd.b2);
                if( !result.colinfo.collides )
                {
                    DispatchCollisionEvent(&Broadphase::EmitCollisionExit, cpd.b1, cpd.b2);
                }
            }
        }
    }

protected:
    void CollisionHappened( Body& b1, Body& b2, CollisionResult cr )
    {
        m_collisions.push_back(CollisionPairData(b1, b2));
        DispatchCollisionEvent(&Broadphase::EmitCollisionEnter, b1, b2, cr);
    }
    
    CollisionResult Resolve( const Body& b1, const Body& b2 ) const
    {
        CollisionResult cr;
        cr.colinfo = Narrowphase().Resolve(b1, b2);
        cr.b1 = &b1;
        cr.b2 = &b2;
        return cr;
    }

    const NarrowphaseType& Narrowphase() const
    {
        return m_narrowphase;
    }

private:
    std::vector<ICollisionListener*> m_collisionListeners;
    NarrowphaseType m_narrowphase;
    std::vector<CollisionPairData> m_collisions;

};


}

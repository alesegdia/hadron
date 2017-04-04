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


template <typename NarrowphaseType>
class Broadphase {
public:

    virtual ~Broadphase() {

    }

    virtual void step() = 0 ;

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
    void collisionHappened( const Body& b1, const Body& b2 )
    {
        for( auto listener : m_collisionListeners )
        {
            listener->collisionHappened( b1, b2 );
        }
    }

private:
    std::vector<ICollisionListener*> m_collisionListeners;
    NarrowphaseType m_narrowphase;

};


}
}

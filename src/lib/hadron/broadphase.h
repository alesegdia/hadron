#pragma once

#include <vector>

#include "body.h"

namespace hadron {
namespace collision {

/**
 * We care about CollisionListener memory management only if it's registered on shutdown
 */
class ICollisionListener {

public:

    virtual ~ICollisionListener() = 0 ;

    /**
     * @brief collisionHappened
     * @param b1
     * @param b2
     */
    virtual void collisionHappened( const Body& b1, const Body& b2 ) = 0;

};

class Broadphase {
public:

    virtual void step() = 0 ;

    virtual void registerBody( Body::Ptr body ) = 0 ;
    virtual void unregisterBody( Body::Ptr body ) = 0 ;

    void registerListener( ICollisionListener* listener );
    void unregisterListener( ICollisionListener* listener );

protected:
    void collisionHappened( const Body& b1, const Body& b2 );

private:
    std::vector<ICollisionListener*> m_collisionListeners;

};

class BruteForceBroadphase : public Broadphase
{
public:

    BruteForceBroadphase();
    virtual ~BruteForceBroadphase();

    void step() override;

    void registerBody( Body::Ptr body ) override;

    /**
     * @brief removeBody
     * @param body
     */
    void unregisterBody( Body::Ptr body ) override;

private:

    std::vector<Body::Ptr> m_bodies;


};

}
}

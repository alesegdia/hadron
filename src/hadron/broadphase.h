#pragma once

#include "body.h"

namespace hadron {
namespace collision {

class Broadphase {
public:

    virtual void step() = 0 ;

    virtual void registerBody( Body* body ) = 0 ;
    virtual void unregisterBody( Body* body ) = 0 ;

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

    BruteForceBroadphase()
    {

    }

    virtual ~BruteForceBroadphase()
    {
        for( auto body : m_bodies )
        {
            delete body;
        }
    }

    void step() override
    {
        for( int idb1 = 0; idb1 < m_bodies.size(); idb1++ )
        {
            for( int idb2 = idb1 + 1; idb2 < m_bodies.size(); idb2++ )
            {
                const Body& b1 = *m_bodies[idb1];
                const Body& b2 = *m_bodies[idb2];

                if( true == Body::collides( b1, b2 ) )
                {
                    collisionHappened( b1, b2 );
                }
            }
        }
    }

    void registerBody( Body* body ) override
    {
        m_bodies.push_back( body );
        return *m_bodies.end();
    }

    /**
     * @brief removeBody
     * @param body
     */
    void unregisterBody( Body* body ) override
    {
        m_bodies.erase( std::remove( m_bodies.begin(), m_bodies.end(), body ), m_bodies.end() );
    }

private:

    std::vector<Body*> m_bodies;


};

}
}

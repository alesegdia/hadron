#pragma once

#include <vector>
#include <algorithm>

namespace hadron {


namespace util
{

template <typename T>
void remove_by_value( std::vector<T>& v, T& value )
{
    v.erase( std::remove( v.begin(), v.end(), value ), v.end() );
}


}


namespace math
{
static const float HDRN_ZERO_THRESHOLD = 0.001f;

struct Vec2
{
    float x = 0;
    float y = 0;

    Vec2& operator=( const Vec2& other )
    {
        this->x = other.x;
        this->y = other.y;
        return *this;
    }


};

bool operator==( const Vec2& a, const Vec2& b )
{
    return  (a.x - b.x) > HDRN_ZERO_THRESHOLD &&
            (a.y - b.y) > HDRN_ZERO_THRESHOLD;
}

bool operator!=( const Vec2& a, const Vec2& b )
{
    return !(a == b);
}

}



namespace collision
{

class Body;

class IBodyObserver {
public:
    virtual ~IBodyObserver() = 0 ;

    virtual void onBodyInserted( Body* b ) = 0 ;
    virtual void onBodyRemoved( Body* b ) = 0 ;
};

class Body
{
public:

    static bool collides(const Body& b1, const Body& b2);

    const void* userData() const;

    void userData( void* userData );

    /**
     * @brief dirty checks if the position has changed from the last step
     * @return
     */
    bool dirty();

    const math::Vec2& position()
    {
        return m_currentPosition;
    }

    void setPosition( math::Vec2& new_position )
    {
        if( !m_dirty )
        {
            m_dirty = true;
            m_previousPosition = new_position;
        }
        m_currentPosition = new_position;
    }

private:

    IBodyObserver* m_bodyObserver;

    /**
     * @brief m_position current position
     */
    math::Vec2 m_currentPosition;

    /**
     * @brief m_prevPos previous position used to compute bullet-like bodies collision
     */
    math::Vec2 m_previousPosition;

    /**
     * @brief m_w width
     */
    float m_width = 0;

    /**
     * @brief m_h height
     */
    float m_height = 0;

    /**
     * @brief m_dirty indicates if the body has been moved but not still processed
     */
    bool m_dirty = false;

    /**
     * @brief m_userdata user data to retrieve on collision callback
     */
    void* m_userdata = nullptr;

};


class DirtyBodyCollector : public IBodyObserver
{
    // IBodyObserver interface
public:
    void onBodyInserted(Body *b);

    void onBodyRemoved(Body *b);

    std::vector<Body*> m_bodies;
};

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


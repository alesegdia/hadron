#pragma once

#include <vector>
#include <algorithm>

#include "math.h"
#include "util.h"
#include "body.h"
#include "broadphase.h"
#include "narrowphase.h"
#include "world.h"

namespace hadron {



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

    float x() const {
        return m_currentPosition.x;
    }

    float y() const {
        return m_currentPosition.y;
    }

    float width() const {
        return m_width;
    }

    float height() const {
        return m_height;
    }

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
>>>>>>> bbc77e5a38ca79f576998dd857316ca534704dfe:src/lib/hadron/hadron.h


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

class World {
public:
    
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

    BruteForceBroadphase();

    virtual ~BruteForceBroadphase();

    void step() override;

    void registerBody( Body* body ) override;

    /**
     * @brief removeBody
     * @param body
     */
    void unregisterBody( Body* body ) override;

private:

    std::vector<Body*> m_bodies;


};

}

}
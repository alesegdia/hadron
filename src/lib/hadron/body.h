#pragma once

#include "math.h"

#include <iostream>

namespace hadron {
namespace collision {


struct AABB
{
    AABB() : x(0), y(0), width(0), height(0) {}
    AABB(float x_, float y_, float w_, float h_)
        : x(x_), y(y_), width(w_), height(h_) {}
    float x, y, width, height;
};


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
    Body(const AABB& aabb)
    {
        this->aabb(aabb);
    }

    Body(float x, float y, float w, float h)
    {
        this->aabb(AABB(x, y, w, h));
    }

    Body()
    {

    }

    typedef Body* Ptr;
    void aabb(const AABB& other)
    {
        this->m_aabb = other;
    }

    static bool collides(const Body& b1, const Body& b2);

    void *userData();

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

    void destroy()
    {
        if( m_alive )
        {
            std::cout << "WARNING: trying to destroy an already dead body" << std::endl;
        }
        m_alive = false;
    }

    AABB m_aabb;

    const AABB& aabb() const
    {
        return m_aabb;
    }

private:

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

    bool m_alive = true;



};


}
}

#pragma once

#include <iostream>

#include "math.h"
#include "aabb.h"


namespace hadron {

class Body
{
public:
    Body(const AABB& aabb);

    Body(float x, float y, float w, float h);

    Body();

    typedef Body* Ptr;
    void GetAABB(const AABB& other);

    void* GetUserData();

    void SetUserData( void* userData );

    /**
     * @brief dirty checks if the position has changed from the last step
     * @return
     */
    bool IsDirty();

    const Vec2& GetPosition();

    void SetPosition( const Vec2& new_position );

    void SetPosition( float x, float y );

    void Destroy();

    void ClearDirty();

    const AABB& GetAABB() const;

private:

	AABB m_aabb;

    void Internal_SetPosition(float x, float y);

    /**
     * @brief m_position current position
     */
    Vec2 m_currentPosition;

    /**
     * @brief m_prevPos previous position used to compute bullet-like bodies collision
     */
    Vec2 m_previousPosition;

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
    bool m_dirty = true;

    /**
     * @brief m_userdata user data to retrieve on collision callback
     */
    void* m_userdata = nullptr;

    bool m_alive = true;



};


}

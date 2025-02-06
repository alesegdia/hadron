#pragma once

#include <iostream>

#include "math.h"
#include "aabb.h"

namespace hadron {

    /**
     * @brief Class representing a physical body with an Axis-Aligned Bounding Box (AABB).
     */
    class Body
    {
    public:
        /**
         * @brief Constructs a Body with a given AABB.
         *
         * @param aabb The AABB to initialize the Body with.
         */
        Body(const AABB& aabb);

        /**
         * @brief Constructs a Body with given position and dimensions.
         *
         * @param x The x-coordinate of the Body.
         * @param y The y-coordinate of the Body.
         * @param w The width of the Body.
         * @param h The height of the Body.
         */
        Body(float x, float y, float w, float h);

        /**
         * @brief Default constructor initializing the Body.
         */
        Body();

        typedef Body* Ptr;

        /**
         * @brief Sets the AABB of the Body.
         *
         * @param other The AABB to set.
         */
        void GetLocalAABB(const AABB& other);

        /**
         * @brief Gets the user data associated with the Body.
         *
         * @return A pointer to the user data.
         */
        void* GetUserData();

        /**
         * @brief Sets the user data associated with the Body.
         *
         * @param userData A pointer to the user data.
         */
        void SetUserData(void* userData);

        /**
         * @brief Checks if the position has changed from the last step.
         *
         * @return true if the position has changed, false otherwise.
         */
        bool IsDirty();

        /**
         * @brief Gets the current position of the Body.
         *
         * @return A reference to the current position vector.
         */
        const Vec2& GetPosition();

        /**
         * @brief Sets the position of the Body.
         *
         * @param new_position The new position vector.
         */
        void SetPosition(const Vec2& new_position);

        /**
         * @brief Sets the position of the Body.
         *
         * @param x The new x-coordinate.
         * @param y The new y-coordinate.
         */
        void SetPosition(float x, float y);

        /**
         * @brief Destroys the Body.
         */
        void Destroy();

        /**
         * @brief Clears the dirty flag.
         */
        void ClearDirty();

        /**
         * @brief Gets the AABB of the Body.
         *
         * @return A reference to the AABB.
         */
        const AABB& GetLocalAABB() const;

    private:
        AABB m_aabb; ///< The Axis-Aligned Bounding Box of the Body.

        /**
         * @brief Sets the position of the Body internally.
         *
         * @param x The new x-coordinate.
         * @param y The new y-coordinate.
         */
        void Internal_SetPosition(float x, float y);

        Vec2 m_currentPosition; ///< The current position of the Body.
        Vec2 m_previousPosition; ///< The previous position of the Body used for collision detection.
        float m_width = 0; ///< The width of the Body.
        float m_height = 0; ///< The height of the Body.
        bool m_dirty = true; ///< Indicates if the Body has been moved but not yet processed.
        void* m_userdata = nullptr; ///< User data associated with the Body.
        bool m_alive = true; ///< Indicates if the Body is alive.
    };

}
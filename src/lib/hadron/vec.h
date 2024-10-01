#pragma once

namespace hadron {

    /**
     * @brief A small constant value used for floating-point comparisons.
     */
    static const float HADRON_EPSILON = 0.000000001f;

    /**
     * @brief A 2D vector class.
     */
    struct Vec2
    {
        /**
         * @brief Default constructor for Vec2.
         */
        Vec2() {}

        /**
         * @brief Parameterized constructor for Vec2.
         *
         * @param x_ The x-coordinate of the vector.
         * @param y_ The y-coordinate of the vector.
         */
        Vec2(float x_, float y_) : x(x_), y(y_) {}

        float x = 0; ///< The x-coordinate of the vector.
        float y = 0; ///< The y-coordinate of the vector.

        /**
         * @brief Assignment operator for Vec2.
         *
         * @param other The other Vec2 to assign from.
         * @return A reference to this Vec2.
         */
        Vec2& operator=(const Vec2& other)
        {
            this->x = other.x;
            this->y = other.y;
            return *this;
        }
    };

    /**
     * @brief Equality operator for Vec2.
     *
         * @param a The first Vec2 to compare.
         * @param b The second Vec2 to compare.
         * @return True if the vectors are equal, false otherwise.
     */
    bool operator==(const Vec2& a, const Vec2& b);

    /**
     * @brief Inequality operator for Vec2.
     *
     * @param a The first Vec2 to compare.
     * @param b The second Vec2 to compare.
     * @return True if the vectors are not equal, false otherwise.
     */
    bool operator!=(const Vec2& a, const Vec2& b);

}
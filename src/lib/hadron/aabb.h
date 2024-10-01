#pragma once

#include "vec.h"

namespace hadron {

    /**
     * @brief Structure to hold collision information.
     */
    struct CollisionInfo
    {
        bool left;    ///< Indicates if the collision is on the left side.
        bool top;     ///< Indicates if the collision is on the top side.
        bool collides; ///< Indicates if a collision occurred.
    };

    /**
     * @brief Axis-Aligned Bounding Box (AABB) structure.
     */
    struct AABB
    {
        /**
         * @brief Checks for collision between two AABBs.
         *
         * @param b1 The first AABB.
         * @param b2 The second AABB.
         * @return CollisionInfo Structure containing collision details.
         */
        static CollisionInfo CheckCollision(const AABB& b1, const AABB& b2)
        {
            bool c = Collides(b1, b2);
            CollisionInfo ci;
            if (c)
            {
                ci = ComputeOrientation(b1, b2);
            }
            ci.collides = c;
            return ci;
        }

        /**
         * @brief Determines if two AABBs collide.
         *
         * @param b1 The first AABB.
         * @param b2 The second AABB.
         * @return true if the AABBs collide, false otherwise.
         */
        static bool Collides(const AABB& b1, const AABB& b2);

        /**
         * @brief Computes the orientation of the collision between two AABBs.
         *
         * @param b1 The first AABB.
         * @param b2 The second AABB.
         * @return CollisionInfo Structure containing orientation details of the collision.
         */
        static CollisionInfo ComputeOrientation(const AABB& b1, const AABB& b2);

        /**
         * @brief Default constructor initializing AABB to zero.
         */
        AABB() : x(0), y(0), width(0), height(0) {}

        /**
         * @brief Parameterized constructor to initialize AABB with given values.
         *
         * @param x_ The x-coordinate of the AABB.
         * @param y_ The y-coordinate of the AABB.
         * @param w_ The width of the AABB.
         * @param h_ The height of the AABB.
         */
        AABB(float x_, float y_, float w_, float h_)
            : x(x_), y(y_), width(w_), height(h_) {}

        float x;      ///< The x-coordinate of the AABB.
        float y;      ///< The y-coordinate of the AABB.
        float width;  ///< The width of the AABB.
        float height; ///< The height of the AABB.
    };

}
#pragma once

#include "body.h"

namespace hadron {

    /**
     * @brief Structure to hold the result of a collision.
     */
    struct CollisionResult {
        const Body* b1; ///< Pointer to the first Body involved in the collision.
        const Body* b2; ///< Pointer to the second Body involved in the collision.
        CollisionInfo colinfo; ///< Information about the collision.
    };

    /**
     * @brief Interface for listening to collision events.
     */
    class ICollisionListener {
    public:
        /**
         * @brief Virtual destructor for ICollisionListener.
         */
        virtual ~ICollisionListener() = 0;

        /**
         * @brief Called when a collision starts.
         *
         * @param b1 Reference to the first Body involved in the collision.
         * @param b2 Reference to the second Body involved in the collision.
         * @param cr The result of the collision.
         */
        virtual void OnCollisionEnter(Body& b1, Body& b2, CollisionResult cr);

        /**
         * @brief Called when a collision is ongoing.
         *
         * @param b1 Reference to the first Body involved in the collision.
         * @param b2 Reference to the second Body involved in the collision.
         */
        virtual void OnCollisionStay(Body& b1, Body& b2);

        /**
         * @brief Called when a collision ends.
         *
         * @param b1 Reference to the first Body involved in the collision.
         * @param b2 Reference to the second Body involved in the collision.
         */
        virtual void OnCollisionExit(Body& b1, Body& b2);
    };

}
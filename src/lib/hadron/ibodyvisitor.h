#pragma once

#include "body.h"

namespace hadron {

    /**
     * @brief Interface for visiting Body objects.
     */
    class IBodyVisitor
    {
    public:
        /**
         * @brief Virtual destructor for IBodyVisitor.
         */
        virtual ~IBodyVisitor() = 0;

        /**
         * @brief Visits a Body object.
         *
         * @param body A pointer to the Body object to visit.
         */
        virtual void visit(Body::Ptr body) = 0;
    };

}
#pragma once

#include "broadphase.h"
#include "../narrowphase/aabbnarrowphase.h"
#include <vector>
#include <memory>

namespace hadron {
    namespace collision {

        /**
         * @brief Class implementing a quadtree-based broadphase collision detection.
         */
        class QuadTreeBroadPhase : public Broadphase<AABBNarrowphase>
        {
        public:
            /**
             * @brief Constructs a QuadTreeBroadPhase object.
             */
            QuadTreeBroadPhase();

            /**
             * @brief Destructor for QuadTreeBroadPhase.
             */
            virtual ~QuadTreeBroadPhase();

            /**
             * @brief Steps the broadphase collision detection.
             */
            void Step() override;

            /**
             * @brief Registers a body for collision detection.
             *
             * @param body The body to register.
             */
            void RegisterBody(Body::Ptr body) override;

            /**
             * @brief Unregisters a body from collision detection.
             *
             * @param body The body to unregister.
             */
            void UnregisterBody(Body::Ptr body) override;

            /**
             * @brief Visits all registered bodies.
             *
             * @param visitor The visitor to apply to each body.
             */
            void Visit(IBodyVisitor* visitor) override;

            /**
             * @brief Queries bodies within a given AABB.
             *
             * @param aabb The AABB to query.
             * @return A vector of bodies within the AABB.
             */
            std::vector<Body*> QueryAABB(const AABB& aabb) override;

        private:
            /**
             * @brief Structure representing a node in the quadtree.
             */
            struct QuadTreeNode
            {
                AABB bounds; ///< The bounds of the node.
                std::vector<Body::Ptr> bodies; ///< The bodies contained in the node.
                std::unique_ptr<QuadTreeNode> children[4]; ///< The children nodes.

                /**
                 * @brief Constructs a QuadTreeNode with given bounds.
                 *
                 * @param bounds The bounds of the node.
                 */
                QuadTreeNode(const AABB& bounds) : bounds(bounds) {}
            };

            /**
             * @brief Subdivides a quadtree node into four children.
             *
             * @param node The node to subdivide.
             */
            void Subdivide(QuadTreeNode& node);

            /**
             * @brief Inserts a body into the quadtree.
             *
             * @param node The node to insert the body into.
             * @param body The body to insert.
             */
            void Insert(QuadTreeNode& node, Body::Ptr body);

            /**
             * @brief Queries bodies within a given AABB in the quadtree.
             *
             * @param node The node to query.
             * @param aabb The AABB to query.
             * @param result The vector to store the result.
             */
            void Query(QuadTreeNode& node, const AABB& aabb, std::vector<Body*>& result);

            std::unique_ptr<QuadTreeNode> m_root; ///< The root node of the quadtree.
            size_t m_maxBodiesPerNode = 4; ///< The maximum number of bodies per quadtree node.
            size_t m_maxDepth = 5; ///< The maximum depth of the quadtree.
        };

    } // namespace collision
} // namespace hadron
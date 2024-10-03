#include "quadtreebroadphase.h"

namespace hadron {
	namespace collision {

		/*
		QuadTreeBroadPhase::QuadTreeBroadPhase()
		{
			// Initialize the root node with a large enough AABB to cover the entire space
			m_root = std::make_unique<QuadTreeNode>(AABB(0, 0, 1000, 1000));
		}

		QuadTreeBroadPhase::~QuadTreeBroadPhase() = default;

		void QuadTreeBroadPhase::Step()
		{
			// Clear the quadtree and reinsert all bodies
			m_root = std::make_unique<QuadTreeNode>(AABB(0, 0, 1000, 1000));
			for (const auto& body : m_bodies)
			{
				Insert(*m_root, body);
			}
		}

		void QuadTreeBroadPhase::RegisterBody(Body::Ptr body)
		{
			m_bodies.push_back(body);
			Insert(*m_root, body);
		}

		void QuadTreeBroadPhase::UnregisterBody(Body::Ptr body)
		{
			auto it = std::remove(m_bodies.begin(), m_bodies.end(), body);
			m_bodies.erase(it, m_bodies.end());
			Step(); // Rebuild the quadtree
		}

		void QuadTreeBroadPhase::Visit(IBodyVisitor* visitor)
		{
			for (const auto& body : m_bodies)
			{
				visitor->visit(body);
			}
		}

		std::vector<Body*> QuadTreeBroadPhase::QueryAABB(const AABB& aabb)
		{
			std::vector<Body*> result;
			Query(*m_root, aabb, result);
			return result;
		}

		void QuadTreeBroadPhase::Subdivide(QuadTreeNode& node)
		{
			float halfWidth = node.bounds.width / 2.0f;
			float halfHeight = node.bounds.height / 2.0f;
			float x = node.bounds.x;
			float y = node.bounds.y;

			node.children[0] = std::make_unique<QuadTreeNode>(AABB(x, y, halfWidth, halfHeight));
			node.children[1] = std::make_unique<QuadTreeNode>(AABB(x + halfWidth, y, halfWidth, halfHeight));
			node.children[2] = std::make_unique<QuadTreeNode>(AABB(x, y + halfHeight, halfWidth, halfHeight));
			node.children[3] = std::make_unique<QuadTreeNode>(AABB(x + halfWidth, y + halfHeight, halfWidth, halfHeight));
		}

		void QuadTreeBroadPhase::Insert(QuadTreeNode& node, Body::Ptr body)
		{
			if (!AABB::Collides(node.bounds, body->m_aabb))
			{
				return;
			}

			if (node.bodies.size() < m_maxBodiesPerNode || node.children[0] == nullptr)
			{
				node.bodies.push_back(body);
			}
			else
			{
				if (node.children[0] == nullptr)
				{
					Subdivide(node);
				}

				for (auto& child : node.children)
				{
					Insert(*child, body);
				}
			}
		}

		void QuadTreeBroadPhase::Query(QuadTreeNode& node, const AABB& aabb, std::vector<Body*>& result)
		{
			if (!AABB::Collides(node.bounds, aabb))
			{
				return;
			}

			for (const auto& body : node.bodies)
			{
				if (AABB::Collides(body->m_aabb, aabb))
				{
					result.push_back(body.get());
				}
			}

			if (node.children[0] != nullptr)
			{
				for (auto& child : node.children)
				{
					Query(*child, aabb, result);
				}
			}
		}
		*/
	} // namespace collision
} // namespace hadron
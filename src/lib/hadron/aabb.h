#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/perpendicular.hpp>
#include "vec.h"


namespace hadron {

    class ConvexHull
    {
	public:
        ConvexHull() = default;

        ConvexHull(const std::vector<glm::fvec3>& vertices)
			: m_vertices(vertices)
		{
		}

		void AddVertex(const glm::fvec3& vertex)
		{
			m_vertices.push_back(vertex);
		}

		void AddVertices(const std::vector<glm::fvec3>& vertices)
		{
			m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());
		}

		const std::vector<glm::fvec3>& GetVertices() const
		{
			return m_vertices;
		}

		void SetVertices(const std::vector<glm::fvec3>& vertices)
		{
			m_vertices = vertices;
		}

		void Clear()
		{
			m_vertices.clear();
		}

        bool CollideWith(const ConvexHull& other) const {
            // Check for collision using the Separating Axis Theorem (SAT)
            std::vector<glm::fvec3> axes = GetAxes();
            std::vector<glm::fvec3> otherAxes = other.GetAxes();
            axes.insert(axes.end(), otherAxes.begin(), otherAxes.end());

            for (const auto& axis : axes) {
                float min1, max1, min2, max2;
                ProjectOntoAxis(axis, min1, max1);
                other.ProjectOntoAxis(axis, min2, max2);

                if (max1 < min2 || max2 < min1) {
                    return false; // No collision
                }
            }

            return true; // Collision detected
        }

	private:
	    std::vector<glm::fvec3> m_vertices;

        std::vector<glm::fvec3> GetAxes() const {
            std::vector<glm::fvec3> axes;
            for (size_t i = 0; i < m_vertices.size(); i++) {
                glm::fvec3 p1 = m_vertices[i];
                glm::fvec3 p2 = m_vertices[(i + 1) % m_vertices.size()];
                glm::fvec3 edge = p2 - p1;
                glm::fvec3 normal = glm::cross(edge, glm::fvec3(0, 0, 1)); // Perpendicular vector in 3D
                axes.push_back(glm::normalize(normal));
            }
            return axes;
        }

        void ProjectOntoAxis(const glm::fvec3& axis, float& min, float& max) const {
            min = FLT_MAX;
            max = -FLT_MAX;
            for (const auto& vertex : m_vertices) {
                float projection = glm::dot(vertex, axis);
                if (projection < min) {
                    min = projection;
                }
                if (projection > max) {
                    max = projection;
                }
            }
        }


    };

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
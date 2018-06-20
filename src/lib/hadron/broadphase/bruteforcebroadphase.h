#pragma once

#include "broadphase.h"
#include "../narrowphase/aabbnarrowphase.h"

namespace hadron {
namespace collision {


class BruteForceBroadphase : public Broadphase<AABBNarrowphase>
{
public:

    BruteForceBroadphase();
    virtual ~BruteForceBroadphase();

    void step() override;

    void registerBody( Body::Ptr body ) override;

    /**
     * @brief removeBody
     * @param body
     */
    void unregisterBody( Body::Ptr body ) override;

    void visit(IBodyVisitor *visitor) override;

    virtual std::vector<Body*> queryAABB( const AABB& aabb )
    {
        std::vector<Body*> ret;
        Body test_body(aabb);
        for( size_t i = 0; i < m_bodies.size(); i++ )
        {
            if( resolve(test_body, *m_bodies[i]) )
            {
                ret.push_back(m_bodies[i]);
            }
        }
        return ret;
    }


private:

    std::vector<Body::Ptr> m_bodies;


};


}
}

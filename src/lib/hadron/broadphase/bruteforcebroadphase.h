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

    void Step() override;

    void RegisterBody( Body::Ptr body ) override;

    /**
     * @brief removeBody
     * @param body
     */
    void UnregisterBody( Body::Ptr body ) override;

    void Visit(IBodyVisitor *visitor) override;

    virtual std::vector<Body*> QueryAABB( const AABB& aabb )
    {
        std::vector<Body*> ret;
        Body test_body(aabb);
        for( size_t i = 0; i < m_bodies.size(); i++ )
        {
            auto result = Resolve(test_body, *m_bodies[i]);
            if( result.colinfo.collides )
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

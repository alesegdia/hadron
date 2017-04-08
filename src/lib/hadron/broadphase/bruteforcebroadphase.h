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

    virtual std::vector<Body*>&& queryAABB( const AABB& aabb )
    {
        Body b(aabb);
        std::vector<Body*> ret;
        for( int i = 0; i < m_bodies.size(); i++ )
        {
            Body::Ptr b2 = m_bodies[i];
            if( resolve(b, *b2) )
            {
                ret.push_back(b2);
            }
        }
        return std::move(ret);
    }

    /**
     * @brief removeBody
     * @param body
     */
    void unregisterBody( Body::Ptr body ) override;

    void visit(IBodyVisitor *visitor) override;

private:

    std::vector<Body::Ptr> m_bodies;


};


}
}

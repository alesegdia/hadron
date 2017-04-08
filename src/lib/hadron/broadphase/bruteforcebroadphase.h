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

    virtual std::vector<Body*>&& queryAABB( const AABB& aabb )
    {
        std::vector<Body*> ret;
        return std::move(ret);
    }


private:

    std::vector<Body::Ptr> m_bodies;


};


}
}

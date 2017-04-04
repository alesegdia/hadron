#pragma once

#include "ibodyvisitor.h"

namespace hadron {
namespace collision {

template <typename BroadphaseType>
class WorldImpl {
public:
    WorldImpl()
    {
        //m_broadphase.setNarrowphase(m_narrowphase);
    }

    void insertBody(Body::Ptr body)
    {
        m_broadphase.registerBody(body);
    }

    void removeBody(Body::Ptr body)
    {
        m_broadphase.unregisterBody(body);
    }

    void visit(IBodyVisitor* visitor)
    {
        m_broadphase.visit(visitor);
    }

private:
    BroadphaseType m_broadphase;

};


typedef WorldImpl<BruteForceBroadphase> World;


}
}

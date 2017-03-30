#pragma once

namespace hadron {
namespace collision {

template <typename BroadphaseType, typename NarrowphaseType>
class WorldImpl {
public:
    WorldImpl()
    {
        m_broadphase.setNarrowphase(m_narrowphase);
    }

    void insertBody(Body::Ptr body)
    {
        m_broadphase.registerBody(body);
    }

    void removeBody(Body::Ptr body)
    {
        m_broadphase.unregisterBody(body);
    }

private:
    BroadphaseType m_broadphase;
    NarrowphaseType m_narrowphase;
};


typedef WorldImpl<BruteForceBroadphase, DumbNarrowphase> World;


}
}

#pragma once

#include "../body.h"

namespace hadron {
namespace collision {

static constexpr int Left = 1;
static constexpr int Right = 2;
static constexpr int Down = 3;
static constexpr int Top = 4;

struct CollisionData {
    Body* b1;
    Body* b2;
    int sideCollision = 0;
};

class Narrowphase
{
public:
    virtual ~Narrowphase();

    virtual CollisionData Resolve(const Body& b1, const Body& b2) const = 0 ;
};

}
}

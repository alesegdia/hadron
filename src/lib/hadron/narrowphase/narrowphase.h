#pragma once

#include "../body.h"

namespace hadron {
namespace collision {

class Narrowphase
{
public:
    virtual ~Narrowphase();

    virtual bool resolve(const Body& b1, const Body& b2) const = 0 ;
};

}
}

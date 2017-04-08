#pragma once

#include "../body.h"

namespace hadron {
namespace collision {

class Narrowphase
{
public:
    virtual ~Narrowphase();

    virtual bool resolve(Body& b1, Body& b2) = 0 ;
};

}
}

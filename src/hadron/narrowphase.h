#pragma once

#include "body.h"

namespace hadron {
namespace collision {

class DumbNarrowphase
{
public:
    virtual bool resolve(Body::Ptr body);
};

}
}

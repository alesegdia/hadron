#pragma once

#include "body.h"

namespace hadron {
namespace collision {

class IBodyVisitor
{
public:
    virtual ~IBodyVisitor() = 0 ;
    virtual void visit( Body::Ptr body ) = 0 ;
};

}
}

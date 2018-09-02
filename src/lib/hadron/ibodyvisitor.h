#pragma once

#include "body.h"

namespace hadron {


class IBodyVisitor
{
public:
    virtual ~IBodyVisitor() = 0 ;
    virtual void visit( Body::Ptr body ) = 0 ;
};


}

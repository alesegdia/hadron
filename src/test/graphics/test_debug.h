#pragma once

#include "workbench/testscreen.h"

class Test_Debug : public TestScreen
{
public:
    Test_Debug() : TestScreen("Test_Debug") {}

    void setup () override
    {
        auto body = new hadron::collision::Body(0, 0, 50, 50);
        addBody(body);
    }
};

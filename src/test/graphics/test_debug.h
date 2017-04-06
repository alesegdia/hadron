#pragma once

#include <hadron/hadron.h>

#include "workbench/testscreen.h"


class Test_Debug : public TestScreen
{
public:
    Test_Debug() : TestScreen("Test_Debug") {}

    void setup () override
    {
        createBody(0, 0, 50, 50);
    }

private:

};

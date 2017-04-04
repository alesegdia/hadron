#pragma once

#include <alligator/alligator.h>

#include <vector>
#include <memory>
#include "testscreen.h"


class Testbed : public Game {
public:

    Testbed( int sw, int sh );
    virtual ~Testbed();

    int create(int argc, char **argv) override;

    void dispose() override;

    void addTest(TestScreen* test)
    {
        this->m_screens.push_back(std::shared_ptr<TestScreen>(test));
    }

    void update(double delta) override
    {
        // handle screen (gui-test) change with keyboard
    }

private:
    std::vector<std::shared_ptr<TestScreen>> m_screens;

};

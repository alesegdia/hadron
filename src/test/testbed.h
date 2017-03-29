#pragma once

#include <alligator/alligator.h>

#include <vector>


class Testbed : public Game {
public:

    Testbed( int sw, int sh );
    virtual ~Testbed();

    int create(int argc, char **argv) override
    {
    }

    void dispose() override;

    void addTest(TestScreen::Ptr test)
    {
        this->m_screens->push_back(test);
    }

    void update(double delta) override
    {
        // handle screen (gui-test) change with keyboard
    }

private:
    std::vector<TestScreen::Ptr> m_screens;

};

#pragma once

#include <alligator/game/iscreen.h>
#include <hadron/hadron.h>

class Testbed : public IScreen
{
public:
    void render() override
    {

    }

private:

    hadron::collision::World m_world;

};

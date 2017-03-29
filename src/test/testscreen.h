#pragma once

#include <alligator/alligator.h>
#include <hadron/hadron.h>

class TestScreen : public IScreen
{
public:
    void update(double delta) override;
    void render();

protected:
    void addBody(Body* b)
    {

    }

private:
    hadron::collision::World m_world;
};

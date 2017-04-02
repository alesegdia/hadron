#pragma once

#include <alligator/alligator.h>
#include <hadron/hadron.h>

class TestScreen : public IScreen
{
public:
	virtual ~TestScreen() = 0;
    void update(double delta) override;
    void render();

protected:
	void addBody(hadron::collision::Body::Ptr b)
    {

    }

private:
    hadron::collision::World m_world;
};

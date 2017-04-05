
#include "testscreen.h"

#include <memory>

TestScreen::~TestScreen()
{

}

void TestScreen::show()
{
    m_world.reset(new hadron::collision::World());
    setup();
}

void TestScreen::hide()
{

}

void TestScreen::update(double delta)
{

}

void TestScreen::render()
{
    m_world->visit(&m_bodyDebugRenderer);
}

void TestScreen::addBody(hadron::collision::Body::Ptr b)
{
    m_world->insertBody(b);
}

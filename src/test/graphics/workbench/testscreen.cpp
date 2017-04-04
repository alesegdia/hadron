
#include "testscreen.h"

#include <memory>

TestScreen::~TestScreen()
{

}

void TestScreen::show()
{
    m_world = std::make_shared<hadron::collision::World>();
}

void TestScreen::hide()
{

}

void TestScreen::update(double delta)
{

}

void TestScreen::render()
{

}

void TestScreen::addBody(hadron::collision::Body::Ptr b)
{
    m_world->insertBody(b);
}


#include "testscreen.h"

#include <memory>

TestScreen::~TestScreen()
{

}

TestScreen::TestScreen(const char *name) : m_name(name) { }

void TestScreen::show()
{
    m_world.reset(new hadron::collision::World());
    setup();
    m_world->registerListener(&m_listener);
}

void TestScreen::hide()
{
    cleanAllEntities();
}

void TestScreen::update(double delta)
{
    step();
    m_world->update();
}

void TestScreen::render()
{
    al_clear_to_color(al_map_rgb(0,0,0));
    m_world->visit(&m_bodyDebugRenderer);
}

const char *TestScreen::name()
{
    return m_name;
}

void TestScreen::cleanAllEntities()
{
    for( auto e : m_entities )
    {
        delete e;
    }
    m_entities.clear();
}

hadron::collision::Body::Ptr TestScreen::createBody(float x, float y, float w, float h)
{
    auto body = new hadron::collision::Body( x, y, w, h );
    m_world->registerBody(body);
    Entity* entity = new Entity();
    m_entities.push_back(entity);
    body->userData(static_cast<void*>(entity));
    return body;
}

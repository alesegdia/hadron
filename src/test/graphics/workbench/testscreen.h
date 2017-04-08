#pragma once

#include <alligator/alligator.h>
#include <hadron/hadron.h>

#include "bodydebugrenderer.h"
#include "entity.h"

class CollisionListener : public hadron::collision::ICollisionListener
{
public:
    void onCollisionEnter(hadron::collision::Body &b1, hadron::collision::Body &b2)
    {
        auto e1 = static_cast<Entity*>(b1.userData());
        auto e2 = static_cast<Entity*>(b2.userData());
        e1->colliding = e2->colliding = true;
    }

    void onCollisionExit(hadron::collision::Body &b1, hadron::collision::Body &b2)
    {
        auto e1 = static_cast<Entity*>(b1.userData());
        auto e2 = static_cast<Entity*>(b2.userData());
        e1->colliding = e2->colliding = false;
    }
};


class TestScreen : public IScreen
{

    typedef hadron::collision::Body::Ptr BodyPtr;
    typedef std::shared_ptr<hadron::collision::World> WorldSharedPtr;

public:
    TestScreen( const char* name );

	virtual ~TestScreen() = 0;

    void show() override;
    void hide() override;

    void update(double delta) override;
    void render() override;

    virtual void setup() = 0 ;

    const char* name();

    void cleanAllEntities();

    virtual void step() = 0 ;

    virtual void draw() = 0 ;

protected:

    BodyPtr createBody(float x, float y, float w, float h);
    std::vector<Entity*>& entities()
    {
        return m_entities;
    }

    WorldSharedPtr world()
    {
        return m_world;
    }

private:

    const char* m_name;

    WorldSharedPtr m_world;
    BodyDebugRenderer m_bodyDebugRenderer;
    std::vector<Entity*> m_entities;
    CollisionListener m_listener;

};

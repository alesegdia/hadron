#pragma once

#include <alligator/alligator.h>
#include <hadron/hadron.h>

#include "bodydebugrenderer.h"


struct Entity
{
    // tells if the entity just started a collision in the last frame
    bool just_collided = false;

    // tells if the entity collides in the last frame
    bool colliding = false;
};

class CollisionListener : public hadron::collision::ICollisionListener
{
public:
    void collisionHappened(const hadron::collision::Body &b1, const hadron::collision::Body &b2)
    {
        auto e1 = static_cast<Entity*>(b1.userData());
        auto e2 = static_cast<Entity*>(b2.userData());
        if( !e1->colliding )
        {
            e1->just_collided = true;
        }
        e1->colliding = true;
        e2->colliding = true;
    }

    void handle
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

protected:

    BodyPtr createBody(float x, float y, float w, float h);

private:

    const char* m_name;

    WorldSharedPtr m_world;
    BodyDebugRenderer m_bodyDebugRenderer;
    std::vector<Entity*> m_entities;

};

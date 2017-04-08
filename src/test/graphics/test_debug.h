#pragma once

#include <hadron/hadron.h>

#include "workbench/testscreen.h"

class BodyKeyboardController
{
public:
    static constexpr float SPEED = 2;
    void attach(hadron::collision::Body::Ptr body)
    {
        m_body = body;
    }

    void step()
    {
        if( m_body )
        {
            float x, y;
            x = y = 0;
            if( Input::IsKeyDown(ALLEGRO_KEY_LEFT) )
            {
                x = -SPEED;
            }
            else if( Input::IsKeyDown(ALLEGRO_KEY_RIGHT) )
            {
                x = SPEED;
            }

            if( Input::IsKeyDown(ALLEGRO_KEY_UP) )
            {
                y = -SPEED;
            }
            else if( Input::IsKeyDown(ALLEGRO_KEY_DOWN) )
            {
                y = SPEED;
            }
            x += m_body->aabb().x;
            y += m_body->aabb().y;
            hadron::math::Vec2 pos(x, y);
            std::cout << x << ", " << y << std::endl;
            m_body->setPosition(pos);
        }
    }

private:
    hadron::collision::Body::Ptr m_body = nullptr;

};

class Test_Debug : public TestScreen
{
public:
    Test_Debug() : TestScreen("Test_Debug") {}

    void setup () override
    {
        auto b = createBody(100, 100, 50, 50);
        createBody(110, 110, 50, 50);
        createBody(200, 100, 30, 30);
        m_bodyKeyCtrl.attach(b);
    }

    void step() override
    {
        m_bodyKeyCtrl.step();
        if( Input::IsMouseButtonJustPressed(1) )
        {
            hadron::collision::AABB queried_aabb( Input::GetMousePosition().x() - 50, Input::GetMousePosition().y() - 50, 100, 100 );
            auto bodies = world()->queryAABB(queried_aabb);
            for( auto body : bodies )
            {
                Entity* e = static_cast<Entity*>(body->userData());
                e->queried = 50;
            }
            m_lastQueried = queried_aabb;
            m_queriedCounter = 100;
        }
        updateEntities();
    }

    void draw() override
    {
        if( m_queriedCounter > 0 )
        {
            const hadron::collision::AABB& r = m_lastQueried;
            al_draw_rectangle(
                        r.x, r.y,
                        r.x + r.width,
                        r.y + r.height,
                        al_map_rgb(255, 0, 255), 1.0f);
        }
    }

    void updateEntities()
    {
        for( Entity* e : entities() )
        {
            e->queried = std::max( e->queried - 1, 0 );
        }
    }

private:
    BodyKeyboardController m_bodyKeyCtrl;
    hadron::collision::AABB m_lastQueried;
    int m_queriedCounter = 0;


};

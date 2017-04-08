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
        auto b = createBody(0, 0, 50, 50);
        createBody(10, 10, 50, 50);
        createBody(100, 100, 30, 30);
        m_bodyKeyCtrl.attach(b);
    }

    void step() override
    {
        m_bodyKeyCtrl.step();
    }

private:
    BodyKeyboardController m_bodyKeyCtrl;


};

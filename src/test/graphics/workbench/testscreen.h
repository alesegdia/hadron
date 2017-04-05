#pragma once

#include <alligator/alligator.h>
#include <hadron/hadron.h>

#include "bodydebugrenderer.h"

class TestScreen : public IScreen
{
public:
    TestScreen( const char* name ) : m_name(name) { }

	virtual ~TestScreen() = 0;

    void show() override;
    void hide() override;

    void update(double delta) override;
    void render() override;

    virtual void setup() = 0 ;

    const char* name()
    {
        return m_name;
    }

protected:
    void addBody(hadron::collision::Body::Ptr b);

private:
    std::shared_ptr<hadron::collision::World> m_world;
    const char* m_name;
    BodyDebugRenderer m_bodyDebugRenderer;

};

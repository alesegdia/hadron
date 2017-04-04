#pragma once

#include <alligator/alligator.h>
#include <hadron/hadron.h>

class TestScreen : public IScreen
{
public:
	virtual ~TestScreen() = 0;

    void show() override;
    void hide() override;

    void update(double delta) override;
    void render() override;

protected:
    void addBody(hadron::collision::Body::Ptr b);

private:
    std::shared_ptr<hadron::collision::World> m_world;

};

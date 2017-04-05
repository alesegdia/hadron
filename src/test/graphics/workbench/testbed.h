#pragma once

#include <alligator/alligator.h>

#include <vector>
#include <memory>
#include "testscreen.h"

#include <allegro5/allegro_font.h>


class Testbed : public Game {
public:

    Testbed( int sw, int sh );
    virtual ~Testbed();

    int create(int argc, char **argv) override;

    void dispose() override;

    void addTest(TestScreen* test);

    void update(double delta) override;

    void render() override;

private:

    void selectScreen(int screen_id);

    std::shared_ptr<TestScreen> selectedScreen();

    std::vector<std::shared_ptr<TestScreen>> m_screens;
    ALLEGRO_FONT* m_font;
    int m_selected = 0;
};

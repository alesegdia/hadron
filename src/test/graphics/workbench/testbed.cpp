#include "testbed.h"

Testbed::Testbed(int sw, int sh)
    : Game( sw, sh )
{

}

Testbed::~Testbed()
{

}

int Testbed::create(int argc, char **argv)
{
    int retcode = 1;
    if( m_screens.size() > 0 ) {
        retcode = 0;
        selectScreen(0);
    }
    m_font = al_load_font("assets/UbuntuMono-R.ttf", 24, 0);
    return retcode;
}

void Testbed::dispose()
{
    al_destroy_font(m_font);
}

void Testbed::addTest(TestScreen *test)
{
    this->m_screens.push_back(std::shared_ptr<TestScreen>(test));
}

void Testbed::update(double delta)
{
    // handle screen (gui-test) change with keyboard
    Game::update(delta);
    if( Input::IsKeyDown(ALLEGRO_KEY_ESCAPE) )
    {
        close();
    }
}

void Testbed::render()
{
    al_clear_to_color(al_map_rgb(0,0,0));
    Game::render();
    al_draw_text(m_font, al_map_rgb(255, 255, 255), 10, 10, 0, selectedScreen()->name());
}

void Testbed::selectScreen(int screen_id)
{
    assert(screen_id >= 0 && screen_id < m_screens.size());
    m_selected = screen_id;
    setScreen(m_screens[screen_id]);
}

std::shared_ptr<TestScreen> Testbed::selectedScreen()
{
    return m_screens[m_selected];
}

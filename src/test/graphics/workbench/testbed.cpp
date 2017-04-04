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
        setScreen(m_screens[0]);
    }
    return retcode;
}

void Testbed::dispose()
{

}

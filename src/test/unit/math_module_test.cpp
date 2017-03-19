
#include <xstf.h>

int main( int argc, char** argv )
{
    XSTF_TESTING("sECS");
    XSTF_ENABLE_VERBOSE_CHECKS;

    {
        XSTF_TEST("Sample test");
        XSTF_ASSERT( 1234 == 1234, "operator== for integer constants" );
    }
    return 0;
}

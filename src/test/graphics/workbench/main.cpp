#include <hadron/hadron.h>

#include "testbed.h"

// HADRON GRAPHIC TESTS
#include "../test_debug.h"

int main(int argc, char** argv) {
    Testbed testbed(800, 600);
    TestScreen::Ptr test_debug = new Test_Debug();
    testbed.addTest(test_debug);
    return testbed.exec(argc, argv);
}

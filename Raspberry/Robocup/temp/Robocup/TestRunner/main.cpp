#include <cstdlib>
#include "extensions/TestFactoryRegistry.h"
#include "extensions/HelperMacros.h"
#include "ui/text/TestRunner.h"

#include "ParseCommandTest.h"
#include "LineDetectTest.h"
#include "LineDetectInfoTest.h"
#include "DetectObjectTest.h"

using namespace std;
using namespace CppUnit;

CPPUNIT_TEST_SUITE_REGISTRATION(ParseCommandTest);
CPPUNIT_TEST_SUITE_REGISTRATION(LineDetectTest);
CPPUNIT_TEST_SUITE_REGISTRATION(LineDetectInfoTest);
CPPUNIT_TEST_SUITE_REGISTRATION(DetectObjectTest);

int main(int argc, char** argv) {
    TextUi::TestRunner runner;
    TestFactoryRegistry &registry = TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    runner.run();
    return 0;
}


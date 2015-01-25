#ifndef DETECTOBJECTTEST_H
#define	DETECTOBJECTTEST_H

#include "TestCase.h"
#include "extensions/HelperMacros.h"

using namespace CppUnit;
using namespace std;

class DetectObjectTest : public TestCase {
    CPPUNIT_TEST_SUITE(DetectObjectTest);
    CPPUNIT_TEST(ImageWithObject);
    CPPUNIT_TEST_SUITE_END();

public:
    DetectObjectTest();
    void ImageWithObject();

private:

};

#endif	/* DETECTOBJECTTEST_H */


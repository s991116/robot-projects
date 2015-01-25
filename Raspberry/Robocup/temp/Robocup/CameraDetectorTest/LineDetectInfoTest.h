#ifndef LINEDETECTINFOTEST_H
#define	LINEDETECTINFOTEST_H

#include "TestCase.h"
#include "extensions/HelperMacros.h"

using namespace CppUnit;
using namespace std;

class LineDetectInfoTest : public TestCase{
    CPPUNIT_TEST_SUITE(LineDetectInfoTest);
    CPPUNIT_TEST(NormalizeLine);
    CPPUNIT_TEST(NormalizeCenterLine);
    CPPUNIT_TEST(NormalizeHalfCenterLine);
    CPPUNIT_TEST_SUITE_END();

public:
    LineDetectInfoTest();
    LineDetectInfoTest(const LineDetectInfoTest& orig);
    virtual ~LineDetectInfoTest();
    
    void NormalizeLine();
    void NormalizeCenterLine();
    void NormalizeHalfCenterLine();
private:

};

#endif	/* LINEDETECTINFOTEST_H */


#include "LineDetectInfoTest.h"
#include "LineInfo.h"

LineDetectInfoTest::LineDetectInfoTest() {
}

LineDetectInfoTest::LineDetectInfoTest(const LineDetectInfoTest& orig) {
}

LineDetectInfoTest::~LineDetectInfoTest() {
}

void LineDetectInfoTest::NormalizeLine() {
    int imageWidth = 100;
    LineInfo* lineInfo = new LineInfo(true, 0, imageWidth);
    
    float normPos = lineInfo->GetNormalizePosition();
    float expected = -1.0;
    double delta = 0.001;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, normPos, delta);
}

void LineDetectInfoTest::NormalizeCenterLine() {
    int imageWidth = 99;
    LineInfo* lineInfo = new LineInfo(true, 50, imageWidth);
    
    float normPos = lineInfo->GetNormalizePosition();
    
    float expected = 0.0;
    double delta = 0.001;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, normPos, delta);
}

void LineDetectInfoTest::NormalizeHalfCenterLine() {
    int imageWidth = 99;
    LineInfo* lineInfo = new LineInfo(true, 25, imageWidth);
    
    float normPos = lineInfo->GetNormalizePosition();
    
    float expected = -0.5;
    double delta = 0.001;
    CPPUNIT_ASSERT_DOUBLES_EQUAL(expected, normPos, delta);
}
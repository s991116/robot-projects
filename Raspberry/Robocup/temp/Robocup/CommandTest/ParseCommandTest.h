#ifndef PARSECOMMANDTEST_H
#define	PARSECOMMANDTEST_H

#include "TestCase.h"
#include "extensions/HelperMacros.h"
#include <string>
#include <vector>
#include "ParseCommandLine.h"

using namespace CppUnit;
using namespace std;

class ParseCommandTest : public TestCase{
    CPPUNIT_TEST_SUITE(ParseCommandTest);
    CPPUNIT_TEST(EmptyLineReturnEmptyCommand);
    CPPUNIT_TEST(LineWithOnlyCommentReturnEmptyCommand);
    CPPUNIT_TEST(LineStartWithPoundReturnCommandType);
    CPPUNIT_TEST(LineWithPoundAndNameReturmCommandName);
    CPPUNIT_TEST(CommandWithNoDataEmptyCommandData);
    CPPUNIT_TEST(LineWithSpacesAndCommand);
    CPPUNIT_TEST(LineWithData);
    CPPUNIT_TEST(LineWithListOfData);
    CPPUNIT_TEST(LineWithNameForDataReturnsDataFromDictionary);
    CPPUNIT_TEST(QuitScriptCommand);
    CPPUNIT_TEST(NoQuitScriptCommand);
    CPPUNIT_TEST(CommandWithNamedArgument);
    CPPUNIT_TEST(CommentBlockStart);
    CPPUNIT_TEST(CommentBlockStartFromEmptyLine);
    CPPUNIT_TEST(CommentBlockStop);
    CPPUNIT_TEST(CommentBlockStopFromEmptyLine);
    CPPUNIT_TEST(CallScript);
    CPPUNIT_TEST(GetSensorInfo);
    CPPUNIT_TEST_SUITE_END();

public:
    ParseCommandTest();
    ParseCommandTest(const ParseCommandTest& orig);
    virtual ~ParseCommandTest();
    void EmptyLineReturnEmptyCommand();
    void LineWithOnlyCommentReturnEmptyCommand();
    void LineStartWithPoundReturnCommandType();
    void LineWithPoundAndNameReturmCommandName();
    void CommandWithNoDataEmptyCommandData();
    void LineWithSpacesAndCommand();
    void LineWithData();
    void LineWithListOfData();
    void LineWithNameForDataReturnsDataFromDictionary();
    void QuitScriptCommand();
    void NoQuitScriptCommand();
    void CommandWithNamedArgument();
    void CommentBlockStart();
    void CommentBlockStartFromEmptyLine();
    void CommentBlockStop();
    void CommentBlockStopFromEmptyLine();
    void CallScript();
    void GetSensorInfo();
    
private:
    CommandData* CreateCommandData(string line);
    std::map<string, int> CreateCommands();
};

#endif	/* PARSECOMMANDTEST_H */
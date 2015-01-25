#include "ParseCommandTest.h"
#include "ParseCommandLine.h"

ParseCommandTest::ParseCommandTest() {
}

ParseCommandTest::ParseCommandTest(const ParseCommandTest& orig) {
}

ParseCommandTest::~ParseCommandTest() {
}

std::map<string, int> ParseCommandTest::CreateCommands()
{
    std::map<string, int> commands;            

    commands["SET_MOTOR_A_KP"] = 4;
    commands["SET_MOTOR_A_KI"] = 5;
    commands["SET_MOTOR_A_KD"] = 6;
    commands["SET_MOTOR_B_KP"] = 7;
    commands["SET_MOTOR_B_KI"] = 8;
    commands["SET_MOTOR_B_KD"] = 9;
    commands["SET_MOVE_BY_DIR"] = 27;
    commands["SET_TICKSPEED_A"] = 1;
    commands["SET_TICKSPEED_B"] = 2;
    return commands;    
}

CommandData* ParseCommandTest::CreateCommandData(string line) {
    std::map<string, int> commands = CreateCommands();
    ParseCommandLine* parseCommandLine = new ParseCommandLine(commands);
    CommandData* command = parseCommandLine->ParseLine(line);
    return command;
}

void ParseCommandTest::QuitScriptCommand() {
    CommandData* command = CreateCommandData("#QUIT //This is a comment.");
    CPPUNIT_ASSERT(command->QuitScript);
}

void ParseCommandTest::NoQuitScriptCommand() {
    CommandData* command = CreateCommandData("//#QUIT //This is a comment.");

    CPPUNIT_ASSERT(!command->QuitScript);
}

void ParseCommandTest::EmptyLineReturnEmptyCommand() {
    CommandData* command = CreateCommandData("");

    CPPUNIT_ASSERT_EQUAL(CommandData::EMPTY, command->Type);
}

void ParseCommandTest::LineWithOnlyCommentReturnEmptyCommand() {
    CommandData* command = CreateCommandData("//This is a comment.");

    CPPUNIT_ASSERT_EQUAL(CommandData::EMPTY, command->Type);    
}

void ParseCommandTest::LineStartWithPoundReturnCommandType() {
    CommandData* command = CreateCommandData(" #//This is a comment.");

    CPPUNIT_ASSERT_EQUAL(CommandData::COMMAND, command->Type);    
}

void ParseCommandTest::LineWithPoundAndNameReturmCommandName() {
    CommandData* command = CreateCommandData(" #CoMmANDnAME//This is a comment.");

    CPPUNIT_ASSERT(command->Name.compare("COMMANDNAME") == 0);    
}

void ParseCommandTest::LineWithSpacesAndCommand() {
    CommandData* command = CreateCommandData("  #COMMANDNAME  //This is a comment...");

    CPPUNIT_ASSERT(command->Name.compare("COMMANDNAME") == 0);
}

void ParseCommandTest::CommandWithNoDataEmptyCommandData() {
    CommandData* command = CreateCommandData("#COMMANDNAME    //Test");    
    int size = command->Data.size();
    CPPUNIT_ASSERT_EQUAL(0, size);
}

void ParseCommandTest::LineWithData() {
    CommandData* command = CreateCommandData("#COMMANDNAME  1234//This is a comment...");    
    std::vector<int> expected;
    expected.push_back(1234);

    CPPUNIT_ASSERT(expected == command->Data);
}

void ParseCommandTest::LineWithListOfData() {
    CommandData* command = CreateCommandData("#COMMANDNAME  1234,123 ,12 , 1 //This is a comment...");
    std::vector<int> expected;
    expected.push_back(1234);
    expected.push_back(123);
    expected.push_back(12);
    expected.push_back(1);

    CPPUNIT_ASSERT(expected == command->Data);
}

void ParseCommandTest::LineWithNameForDataReturnsDataFromDictionary() {
    CommandData* command = CreateCommandData("#SENDDATA SET_MOTOR_A_KI, 300");
    std::vector<int> expected;
    expected.push_back(5);
    expected.push_back(300);    

    CPPUNIT_ASSERT(expected == command->Data);
}

void ParseCommandTest::CommandWithNamedArgument() {
  CommandData* command = CreateCommandData("!FeatureA -SETTINGNAME 300");
  
  CPPUNIT_ASSERT_EQUAL(CommandData::SETTING, command->Type);
  CPPUNIT_ASSERT(command->Name.compare("FEATUREA") == 0);
  CPPUNIT_ASSERT(command->SettingName.compare("SETTINGNAME") == 0);
  CPPUNIT_ASSERT_EQUAL(command->SettingValue, 300);  
}

void ParseCommandTest::CommentBlockStart() {
    std::map<string, int> commands = CreateCommands();
    ParseCommandLine* parseCommandLine = new ParseCommandLine(commands);
    parseCommandLine->ParseLine("#SENDDATA SET_MOTOR_A_KI, 300 /* Comment start");
    CommandData* command = parseCommandLine->ParseLine("#SENDDATA SET_MOTOR_A_KI, 300");
  
    CPPUNIT_ASSERT_EQUAL(CommandData::EMPTY, command->Type);
}

void ParseCommandTest::CommentBlockStop() {
    std::map<string, int> commands = CreateCommands();
    ParseCommandLine* parseCommandLine = new ParseCommandLine(commands);
    parseCommandLine->ParseLine("#SENDDATA SET_MOTOR_A_KI, 300 /* Comment start");
    parseCommandLine->ParseLine("#SENDDATA SET_MOTOR_A_KI, 300");
    CommandData* command = parseCommandLine->ParseLine("Comment end  */   #SENDDATA SET_MOTOR_A_KI, 300");
  
    CPPUNIT_ASSERT_EQUAL(CommandData::COMMAND, command->Type);
}

void ParseCommandTest::CommentBlockStartFromEmptyLine() {
    std::map<string, int> commands = CreateCommands();
    ParseCommandLine* parseCommandLine = new ParseCommandLine(commands);
    parseCommandLine->ParseLine("/*");
    CommandData* command = parseCommandLine->ParseLine("#SENDDATA SET_MOVE_BY_DIR, 0");
  
    CPPUNIT_ASSERT_EQUAL(CommandData::EMPTY, command->Type);
}

void ParseCommandTest::CommentBlockStopFromEmptyLine() {
    std::map<string, int> commands = CreateCommands();
    ParseCommandLine* parseCommandLine = new ParseCommandLine(commands);
    parseCommandLine->ParseLine("/*");
    parseCommandLine->ParseLine("*/");
    CommandData* command = parseCommandLine->ParseLine("#SENDDATA SET_MOTOR_A_KI, 300");
  
    CPPUNIT_ASSERT_EQUAL(CommandData::COMMAND, command->Type);
}


void ParseCommandTest::CallScript() {
  CommandData* command = CreateCommandData(">SubScript.txt");
  
  CPPUNIT_ASSERT_EQUAL(CommandData::CALLSCRIPT, command->Type);
  CPPUNIT_ASSERT(command->CallScriptFilename.compare("SubScript.txt") == 0);
}

void ParseCommandTest::GetSensorInfo() {
  CommandData* command = CreateCommandData("?SENSORNAME");
  
  CPPUNIT_ASSERT_EQUAL(CommandData::SENSORINFO, command->Type);
  CPPUNIT_ASSERT(command->Name.compare("SENSORNAME") == 0);  
}
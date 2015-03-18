#include <iostream>

#include <gtest/gtest.h>
#include <ParseCommandLine.h>

TEST(Set_String_Setting_From_CommandLine, ParseCommandLine)
{
  std::map<string, int> commands;
  ParseCommandLine* sut = new ParseCommandLine(commands);

  CommandData* result = sut->ParseLine("!Test -setting 123");

  EXPECT_TRUE(result->Type == CommandData::SETTING);
  EXPECT_TRUE(result->Name.compare("TEST")==0);
  EXPECT_TRUE(result->SettingName.compare("setting")==0);
  EXPECT_TRUE(result->SettingValue == 123);
}


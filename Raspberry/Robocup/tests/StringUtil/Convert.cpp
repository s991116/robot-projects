#include <iostream>

#include <gtest/gtest.h>
#include <Convert.h>

TEST(Set_Int_Convert, StringUtil)
{
  int testValue = 123;
  std::string expected = "123";
  
  std::string result = Convert::IntToString(testValue);
  
  ASSERT_STREQ(expected.c_str(), result.c_str());
}

TEST(Set_Float_Convert, StringUtil)
{
  float testValue = 1.23f;
  std::string expected = "1.23";
  
  std::string result = Convert::FloatToString(testValue);

  ASSERT_STREQ(expected.c_str(), result.c_str());
}

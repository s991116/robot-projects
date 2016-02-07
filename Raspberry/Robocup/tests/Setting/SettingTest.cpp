#include <iostream>

#include <gtest/gtest.h>
#include <Setting.h>
#include <SettingMock.h>

TEST(Set_Int_Setting, Setting)
{
    int testValue = 123;
    SettingMock* setting = new SettingMock();

    setting->Set(setting->name, testValue);

    int result = setting->valueInt;

    EXPECT_EQ(testValue, result);
}

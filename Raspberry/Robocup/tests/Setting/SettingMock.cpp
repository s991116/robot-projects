#include <SettingMock.h>

SettingMock::SettingMock()
{
  this->name = "test";
  this->SettingsInt[this->name]    = &valueInt;
  this->SettingsFloat[this->name]  = &valueFloat;
  this->SettingsBool[this->name]   = &valueBool;
  this->SettingsString[this->name] = &valueString;
}
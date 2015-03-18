#include <SettingMock.h>

SettingMock::SettingMock()
{
  this->name = "test";
  this->SettingsInt[this->name]    = &valueInt;
}

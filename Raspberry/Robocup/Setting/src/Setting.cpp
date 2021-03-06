#include "Setting.h"

Setting::Setting() {
}

void Setting::Set(std::string name, int value) {

  if(SettingsFloat[name] != NULL)
  {
    SetFloatValue(name, value);
    UpdatedSetting(name);
    return;
  }

  if(SettingsInt[name] != NULL)
  {
    SetIntValue(name, value);
    UpdatedSetting(name);
	return;
  }

  if(SettingsBool[name] != NULL)
  {
    SetBoolValue(name, value);
    UpdatedSetting(name);
	return;
  }

  std::string error = "Could not find setting name '" + name + "'.";
  throw error;
}

void Setting::  UpdatedSetting(std::string name)
{
}

void Setting::SetFloatValue(std::string name, int value) {
  float* setting = SettingsFloat[name];

  if(setting != NULL)
  {
    *setting = value / 100.0;
  }
}

void Setting::SetIntValue(std::string name, int value) {
  int* setting = SettingsInt[name];

  if(setting != NULL)
  {
    *setting = value;
  }
}

void Setting::SetBoolValue(std::string name, int value) {
  bool* setting = SettingsBool[name];

  if(setting != NULL)
  {
    *setting = (value != 0);
  }
}

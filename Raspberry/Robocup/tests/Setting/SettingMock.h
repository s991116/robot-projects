#ifndef SETTINGMOCK_H
#define	SETTINGMOCK_H

#include <Setting.h>

class SettingMock : public Setting
{
  public:
  SettingMock();

  int valueInt;

  std::string name;
};

#endif	/* SETTINGMOCK_H */

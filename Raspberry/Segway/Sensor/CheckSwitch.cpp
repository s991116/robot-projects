#include "CheckSwitch.h"

CheckSwitch::CheckSwitch(Check* timeCheck, Check* pressKeyInfo) {
    _SettingMode = 0;
    this->SettingsInt["MODE"] = &_SettingMode;
    _TimeCheck = timeCheck;
    _PressKeyInfo = pressKeyInfo;
    _Check = _TimeCheck;
}

void CheckSwitch::Prepare() {
    switch(_SettingMode)
    {
        case 0:
            _Check = _TimeCheck;
            break;
        case 1:
            _Check = _PressKeyInfo;
            break;
    }
    _Check->Prepare();
}

bool CheckSwitch::Test() {
    return _Check->Test();
}

CheckSwitch::~CheckSwitch() {
}
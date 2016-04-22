#include "CheckSwitch.h"

CheckSwitch::CheckSwitch(Check* timeCheck, Check* pressKeyInfo, Check* distanceCheck, Check* lineDetected) {
    _SettingMode = 0;
    this->SettingsInt["MODE"] = &_SettingMode;
    _TimeCheck = timeCheck;
    _DistanceCheck = distanceCheck;
    _PressKeyInfo = pressKeyInfo;
    _Check = _TimeCheck;
    _LineDetected = lineDetected;
}

void CheckSwitch::Prepare() {
    switch (_SettingMode) {
        case 0:
            _Check = _TimeCheck;
            break;
            
        case 1:
            _Check = _PressKeyInfo;
            break;

        case 2:
            _Check = _DistanceCheck;
            break;

        case 3:
            _Check = _LineDetected;
            break;
    }
    _Check->Prepare();
}

bool CheckSwitch::Test() {
    return _Check->Test();
}

CheckSwitch::~CheckSwitch() {
}
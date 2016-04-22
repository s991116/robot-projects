#ifndef CHECKSWITCH_H
#define	CHECKSWITCH_H

#include "Check.h"
#include "Setting.h"

class CheckSwitch : public Check, public Setting {
public:
    CheckSwitch(Check* timeCheck, Check* pressKeyInfo, Check* distanceCheck, Check* lineDetected);
    void Prepare();
    bool Test();
    virtual ~CheckSwitch();
private:
    int _SettingMode;
    Check* _Check;
    Check* _TimeCheck;
    Check* _PressKeyInfo;
    Check* _DistanceCheck;
    Check* _LineDetected;
};

#endif	/* CHECKSWITCH_H */


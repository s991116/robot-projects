#ifndef CHECKSWITCH_H
#define	CHECKSWITCH_H

#include "Check.h"
#include "Setting.h"

class CheckSwitch : public Check, public Setting {
public:
    CheckSwitch(Check* timeCheck, Check* pressKeyInfo);
    void Prepare();
    bool Test();
    virtual ~CheckSwitch();
private:
    int _SettingMode;
    Check* _Check;
    Check* _TimeCheck;
    Check* _PressKeyInfo;
};

#endif	/* CHECKSWITCH_H */


#ifndef SWITCHCHECK_H
#define	SWITCHCHECK_H
#include <Check.h>
#include <CheckWithBreak.h>
#include <Setting.h>
#include <ComController.h>

class SwitchCheck : public Check, public Setting {
public:
    enum CheckEnum
    {
      Port,
      Distance,
      LeftLine,
      BottomLine,
      DistanceSensor,
    };
	
    SwitchCheck(ComController* comController, Check* portCheck, Check* distanceCheck, Check* leftLineCheck, Check* bottomLineCheck, Check* distanceSensorCheck);	
    void SetCheck(CheckEnum check);
    void Prepare();
    bool Test();
    	
private:   
	Check* _PortCheck;
	Check* _DistanceCheck;
	Check* _LeftLineCheck;
	Check* _BottomLineCheck;
	Check* _DistanceSensorCheck;
        Check* _CurrentCheck;
        CheckWithBreak* _CurrentCheckWithBreak;
        Check* GetCheck(CheckEnum check);
        int _CheckValue;

};

#endif	/* SWITCHCHECK_H */


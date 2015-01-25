#ifndef FOLLOWLINECOMMAND_H
#define	FOLLOWLINECOMMAND_H

#include "../Sensors/Command.h"
#include "../ArduinoController/ComController.h"
#include "CameraDetector.h"
#include "FollowLineSetting.h"
#include "../Sensors/SwitchCheck.h"
#include "LineDetect.h"

class FollowLineCommand  : public Command {

public:
    FollowLineCommand(CameraDetector* cameraDetector, ComController* comController, FollowLineSetting* _FollowLineSetting, Check* check, LineDetect* bottomLineDetect, LineDetect* topLineDetect);
    virtual ~FollowLineCommand();
    
    std::string Execute(vector<int>);
    
private:
    CameraDetector* _CameraDetector;
    ComController* _ComController;
    FollowLineSetting* _FollowLineSetting;
    Check* _Check;
    LineDetect* _BottomLineDetect;
    LineDetect* _TopLineDetect;
    void PrintPosition(float position);

};

#endif	/* FOLLOWLINECOMMAND_H */


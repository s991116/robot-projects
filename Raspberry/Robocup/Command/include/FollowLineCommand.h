#ifndef FOLLOWLINECOMMAND_H
#define	FOLLOWLINECOMMAND_H

#include <Command.h>
#include <ComController.h>
#include <PiCamera.h>
#include <FollowLineSetting.h>
#include <SwitchCheck.h>
#include <LineDetect.h>

class FollowLineCommand  : public Command {

public:
    FollowLineCommand(PiCamera* piCamera, ComController* comController, FollowLineSetting* _FollowLineSetting, Check* check, LineDetect* bottomLineDetect, LineDetect* topLineDetect);
    virtual ~FollowLineCommand();
    
    std::string Execute(vector<int>);
    
private:
    PiCamera* _PiCamera;
    ComController* _ComController;
    FollowLineSetting* _FollowLineSetting;
    Check* _Check;
    LineDetect* _BottomLineDetect;
    LineDetect* _TopLineDetect;
    void PrintPosition(float position);

};

#endif	/* FOLLOWLINECOMMAND_H */


#ifndef FOLLOWLINECOMMAND_H
#define	FOLLOWLINECOMMAND_H

#include <Command.h>
#include <ComController.h>
#include <RobotCamera.h>
#include <FollowLineSetting.h>
#include <SwitchCheck.h>
#include <LineDetect.h>
#include <Logging.h>

class FollowLineCommand  : public Command {

public:
    FollowLineCommand(RobotCamera* robotCamera, ComController* comController, FollowLineSetting* _FollowLineSetting, Check* check, LineDetect* bottomLineDetect, LineDetect* topLineDetect, Logging* logging);
    virtual ~FollowLineCommand();
    
    std::string Execute(vector<int>);
	std::string Execute();

private:
    RobotCamera* _RobotCamera;
    ComController* _ComController;
    FollowLineSetting* _FollowLineSetting;
    Check* _Check;
    LineDetect* _BottomLineDetect;
    LineDetect* _TopLineDetect;
	Logging* _Logging;
    void PrintPosition(float position);
};

#endif	/* FOLLOWLINECOMMAND_H */
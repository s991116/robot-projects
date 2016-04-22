#ifndef FOLLOWLINEANDWAITCOMMAND_H
#define	FOLLOWLINEANDWAITCOMMAND_H

#include "Command.h"
#include "Setting.h"
#include "Check.h"
#include "CameraSensor.h"
#include "Navigate.h"
#include "Logging.h"

class FollowLineAndWaitCommand : public Command, public Setting {
public:
    FollowLineAndWaitCommand(Check* check, CameraSensor* cameraSensor, Navigate* navigate, Logging* logging);
    std::string Execute(vector<int> input);
    virtual ~FollowLineAndWaitCommand();
private:
    Check* _Check;
    CameraSensor* _CameraSensor;
    Navigate* _Navigate;
    float _SideCorrectionFactor;
    float _SpeedCorrectionFactor;
    float _MaxSpeed;
    Logging* _Logging;
};

#endif	/* FOLLOWLINEANDWAITCOMMAND_H */


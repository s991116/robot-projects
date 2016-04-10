#ifndef FOLLOWLINECOMMAND_H
#define	FOLLOWLINECOMMAND_H

#include "Command.h"
#include "Check.h"
#include "CameraSensor.h"
#include "Setting.h"
#include "Navigate.h"

class FollowLineCommand : public Command , public Setting{
public:
    FollowLineCommand(Check* check, CameraSensor* cameraSensor, Navigate* Navigate);
    std::string Execute(vector<int> input);
    virtual ~FollowLineCommand();
private:
    Check* _Check;
    CameraSensor* _CameraSensor;
    Navigate* _Navigate;
    float _SideCorrectionFactor;
};

#endif	/* FOLLOWLINECOMMAND_H */


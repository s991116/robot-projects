#ifndef NAVIGATECOMMAND_H
#define	NAVIGATECOMMAND_H

#include "Navigate.h"
#include "Setting.h"
#include "Command.h"

class NavigateCommand : public Command, public Setting{
public:
    NavigateCommand(Navigate* navigate);
    std::string Execute(vector<int> input);
    virtual ~NavigateCommand();
private:
    Navigate* _Navigate;
    int _PID_P;
    int _PID_I;
    int _PID_D;
    int _PIDLimit;
    int _SpeedCorrLimit;
    
};

#endif	/* NAVIGATECOMMAND_H */


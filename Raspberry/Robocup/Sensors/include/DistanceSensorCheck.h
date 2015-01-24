#ifndef DISTANCESENSORCHECK_H
#define	DISTANCESENSORCHECK_H

#include "Check.h"
#include "ComController.h"
#include "Setting.h"
#include "Command.h"

class DistanceSensorCheck : public Check, public Setting, public Command {
public:
    DistanceSensorCheck(ComController* comController);

    void Prepare();
    bool Test();
    std::string Execute(vector<int> input);

private:
    ComController* _ComController;
    int MinDistance;
    int MaxDistance;
    bool CheckInRange;
    int ReCheck;
    int PositiveCheck;

};

#endif	/* DISTANCESENSORCHECK_H */


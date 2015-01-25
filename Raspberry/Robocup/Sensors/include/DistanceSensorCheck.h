#ifndef DISTANCESENSORCHECK_H
#define	DISTANCESENSORCHECK_H

#include <Check.h>
#include <ComController.h>
#include <Setting.h>

class DistanceSensorCheck : public Check, public Setting {
public:
    DistanceSensorCheck(ComController* comController);

    void Prepare();
    bool Test();

private:
    ComController* _ComController;
    int MinDistance;
    int MaxDistance;
    bool CheckInRange;
    int ReCheck;
    int PositiveCheck;

};

#endif	/* DISTANCESENSORCHECK_H */


#ifndef DISTANCECHECK_H
#define	DISTANCECHECK_H

#include "Check.h"
#include "Setting.h"
#include "ComController.h"
#include "SensorInfo.h"

class DistanceCheck : public Check, public Setting, public SensorInfo {
public:
    DistanceCheck(ComController* comController, int distance);

    void Prepare();
    bool Test();    

    std::string GetStatus();
    
private:
    ComController* _ComController;
   int _TargetDistance;
};

#endif	/* DISTANCECHECK_H */
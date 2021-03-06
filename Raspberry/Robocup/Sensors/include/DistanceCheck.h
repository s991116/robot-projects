#ifndef DISTANCECHECK_H
#define	DISTANCECHECK_H

#include <Check.h>
#include <Setting.h>
#include <ComController.h>
#include <SensorInfo.h>
#include <Logging.h>

class DistanceCheck : public Check, public Setting, public SensorInfo {
public:
    DistanceCheck(ComController* comController, int distance, Logging* logging);

    void Prepare();
    bool Test();    

    std::string GetStatus();
	void SetDistance(int distance);
    
private:
    ComController* _ComController;
   int _TargetDistance;
   Logging* _Logging;
};

#endif	/* DISTANCECHECK_H */
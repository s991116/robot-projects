#ifndef DISTANCESENSORCHECK_H
#define	DISTANCESENSORCHECK_H

#include <Check.h>
#include <ComController.h>
#include <Setting.h>
#include <SensorInfo.h>
#include <CameraNavigation.h>

class DistanceSensorCheck : public Check, public Setting, public SensorInfo {
public:
    DistanceSensorCheck(ComController* comController, CameraNavigation* cameraNavigation);

    void Prepare();
    bool Test();
    std::string GetStatus();

private:
    ComController* _ComController;
	CameraNavigation* _CameraNavigation;
    int MinDistance;
    int MaxDistance;
    bool CheckInRange;
    int ReCheck;
    int PositiveCheck;
	int Position;
};

#endif	/* DISTANCESENSORCHECK_H */


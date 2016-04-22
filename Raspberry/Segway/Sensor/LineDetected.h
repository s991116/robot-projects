#ifndef LINEDETECTED_H
#define	LINEDETECTED_H

#include "Check.h"
#include "Setting.h"
#include "CameraSensor.h"

class LineDetected : public Check, public Setting {
public:
    LineDetected(CameraSensor* cameraSensor);
    void Prepare();
    bool Test();
    
    virtual ~LineDetected();
private:
    bool _NoLineDetected;
    CameraSensor* _CameraSensor;
};

#endif	/* LINEDETECTED_H */


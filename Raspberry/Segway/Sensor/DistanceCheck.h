#ifndef DISTANCECHECK_H
#define	DISTANCECHECK_H

#include "Distance.h"
#include "Check.h"
#include "Setting.h"

class DistanceCheck : public Check, public Setting {
public:
    DistanceCheck(Distance* distance);
    void Prepare();
    bool Test();
    
    virtual ~DistanceCheck();
private:
    Distance* _Distance;
    int _DistanceToRun;

};

#endif	/* DISTANCECHECK_H */


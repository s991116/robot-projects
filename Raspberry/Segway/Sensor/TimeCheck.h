#ifndef TIMECHECK_H
#define	TIMECHECK_H

#include "Check.h"
#include "Setting.h"
#include "SensorInfo.h"
#include "Navigate.h"
#include <string>
#include <sys/time.h>

class TimeCheck : public Check, public Setting {
public:
    TimeCheck();
    
    void Prepare();
    bool Test();
    
private:
    int _TargetTime;
    int _EndTime;
    virtual ~TimeCheck();
    struct timeval tv;
private:

};

#endif	/* TIMECHECK_H */


#ifndef MOTORVIEW_H
#define	MOTORVIEW_H

#include <Motor.h>

class MotorView {
public:
    MotorView(Motor* motor);
    void View();
    virtual ~MotorView();
private:
    void PrintHelp();
    Motor* _Motor;

};

#endif	/* MOTORVIEW_H */


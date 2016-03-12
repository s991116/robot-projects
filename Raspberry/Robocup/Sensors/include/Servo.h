#ifndef SERVO_H
#define	SERVO_H

#include <SensorInfo.h>
#include <ComController.h>

class Servo : public SensorInfo {
public:
    Servo(ComController* comController, int servoNr);
    Servo(const Servo& orig);
    std::string GetStatus();

private:
    ComController* _ComController;
    int servoNr;
};

#endif	/* SERVO_H */
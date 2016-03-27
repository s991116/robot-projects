#ifndef ROBOT_H
#define	ROBOT_H

#include <ComPort.h>
#include <ComStream.h>
#include <CommunicationHandler.h>
#include <SerialProtocol.h>
#include <HardwareController.h>
#include <Motor.h>
#include <Servo.h>
#include <Gyro.h>
#include <MotorTuning.h>
#include <CameraSensor.h>
#include "LineDetectSetting.h"
#include "LineDetect.h"
#include "Logging.h"

class Robot {
public:
    Robot();
    virtual ~Robot();

    Motor* _Motor;
    MotorTuning* _MotorTuning;
    Gyro* _Gyro;
    Servo* _Servo;
    CameraSensor* _CameraSensor;
    Logging* _Log;
    LineDetectSetting* _BottomLineDetectSetting;
    LineDetect* _BottomLineDetect;
    ComPort* _ComPort;
    ComStream* _ComStream;
    CommunicationHandler* _CommunicationHandler;
    SerialCommandProtocol* _SerialProtocol;

private:
    HardwareController* _HwCtrl;
    
    PiCamera* _Camera;    
    FaceDetection* _FaceDetection;
};
#endif	/* ROBOT_H */
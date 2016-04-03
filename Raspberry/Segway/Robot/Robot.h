#ifndef ROBOT_H
#define	ROBOT_H

#include <ComPort.h>
#include <ComStream.h>
#include <CommunicationHandler.h>
#include <SerialProtocol.h>
#include <Motor.h>
#include <Servo.h>
#include <Gyro.h>
#include <CameraSensor.h>
#include <Navigate.h>
#include "LineDetectSetting.h"
#include "LineDetect.h"
#include "SettingFileReader.h"
#include "SettingReader.h"
#include "Logging.h"
#include "CommandScript.h"

class Robot {
public:
    Robot();
    virtual ~Robot();
    Navigate* _Navigate;
    Motor* _Motor;
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
    CommandScript* _CommandScript;

private:    
    PiCamera* _Camera;    
    FaceDetection* _FaceDetection;
    LineDetect* _LineDetect;
    LineDetectSetting* _LineDetectSetting;
};
#endif	/* ROBOT_H */
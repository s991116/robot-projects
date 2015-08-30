#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <Convert.h>
#include <SoundPlayer.h>
#include <Sounds.h>
#include <HardwareController.h>
#include <ComPort.h>
#include <CommandType.h>
#include "MotorState.h"
#include "GyroState.h"
#include "ServoState.h"
#include "Servo.h"
#include "Gyro.h"
#include "MotorTuningController.h"
#include "MotorTuning.h"
#include "MainState.h"
#include "Motor.h"
#include "CameraState.h"
#include <ncurses.h>


using namespace std;

int main(int argc, char** argv) {

    ComPort* comPort = new ComPort();
    HardwareController* hwCtrl = new HardwareController(comPort);
    Motor* motor = new Motor(hwCtrl);
    MotorTuning* motorTuning = new MotorTuning(hwCtrl);
    Gyro* gyro = new Gyro(hwCtrl);
    Servo* servo = new Servo(hwCtrl);
    PiCamera* camera = new PiCamera();
    FaceDetection* faceDetection = new FaceDetection();
    CameraSensor* cameraSensor = new CameraSensor(camera, faceDetection, servo);
    
    MotorTuningController* motorTuningController = new MotorTuningController(motorTuning, motor);
    State* motorState = new MotorState(motor, motorTuningController);
    State* gyroState = new GyroState(gyro);
    State* servoState = new ServoState(servo);    
    State* cameraState = new CameraState(cameraSensor);
    State* state = new MainState(motorState, gyroState, servoState, cameraState);

    initscr();

    while (state != NULL) {
        state = state->View();
    }

    endwin();

    return 0;
}
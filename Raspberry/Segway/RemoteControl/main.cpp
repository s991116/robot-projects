#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <Convert.h>
#include <SoundPlayer.h>
#include <Sounds.h>
#include <CommandType.h>
#include "MotorTuningController.h"
#include "MotorState.h"
#include "GyroState.h"
#include "ServoState.h"
#include "MainState.h"
#include "CameraState.h"
#include <ncurses.h>
#include <Robot.h>

using namespace std;

int main(int argc, char** argv) {
    Robot* robot = new Robot();
    MotorTuningController* motorTuningController = new MotorTuningController(robot->_MotorTuning, robot->_Motor);
    State* motorState = new MotorState(robot->_Motor, motorTuningController);
    State* gyroState = new GyroState(robot->_Gyro);
    State* servoState = new ServoState(robot->_Servo);    
    State* cameraState = new CameraState(robot->_CameraSensor);
    State* state = new MainState(motorState, gyroState, servoState, cameraState);

    initscr();

    while (state != NULL) {
        state = state->View();
    }

    endwin();

    return 0;
}
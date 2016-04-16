#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <Convert.h>
#include <SoundPlayer.h>
#include <Sounds.h>
#include <CommandType.h>
#include "MotorState.h"
#include "GyroState.h"
#include "ServoState.h"
#include "MainState.h"
#include "CameraState.h"
#include "ComState.h"
#include "NavigateState.h"
#include "ScriptRunnerState.h"
#include "CommandScript.h"
#include <ncurses.h>
#include <Robot.h>

using namespace std;

int main(int argc, char** argv) {
    Robot* robot = new Robot();
    State* motorState = new MotorState(robot->_Motor);
    State* gyroState = new GyroState(robot->_Gyro);
    State* servoState = new ServoState(robot->_Servo);    
    State* cameraState = new CameraState(robot->_CameraSensor);
    State* comState = new ComState(robot->_SerialProtocol);
    State* navigate = new NavigateState(robot->_Navigate, robot->_Distance);
    State* scriptRunner = new ScriptRunnerState(robot->_CommandScript);
    State* state = new MainState(motorState, gyroState, servoState, cameraState, comState, navigate, scriptRunner);

    initscr();

    while (state != NULL) {
        state = state->View();
    }

    endwin();

    return 0;
}
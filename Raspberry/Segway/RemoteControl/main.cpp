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
#include "Gyro.h"
#include "MotorTuningController.h"
#include "MotorTuning.h"
#include "MainState.h"
#include "Motor.h"
#include <ncurses.h>


using namespace std;

int main(int argc, char** argv) {

    ComPort* comPort = new ComPort();
    HardwareController* hwCtrl = new HardwareController(comPort);
    Motor* motor = new Motor(hwCtrl);
    MotorTuning* motorTuning = new MotorTuning(hwCtrl);
    Gyro* gyro = new Gyro(hwCtrl);
    MotorTuningController* motorTuningController = new MotorTuningController(motorTuning, motor);
    State* motorState = new MotorState(motor, motorTuningController);
    State* gyroState = new GyroState(gyro);
    State* state = new MainState(motorState, gyroState);

    initscr();

    while (state != NULL) {
        state = state->View();
    }

    endwin();

    return 0;
}
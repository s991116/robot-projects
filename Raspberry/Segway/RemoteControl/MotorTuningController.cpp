#include "MotorTuningController.h"
#include <unistd.h>
#include <iostream>
#include <fstream>

#define msleep(ms) usleep(1000*ms)

MotorTuningController::MotorTuningController(IMotorTuning* motorTuning, IMotor* motor) {
    _MotorTuning = motorTuning;
    _Motor = motor;
}

MotorTuningController::~MotorTuningController() {
}

void MotorTuningController::RunMeasure() {
    //Stop motor and wait
    SetMotorSpeed(0);
    //Start Measure
    _MotorTuning->StartMeasuring();
    //Set speed
    SetMotorSpeed(50);
    //Wait fixed time
    msleep(500);
    //Set speed
    SetMotorSpeed(-50);
    //Wait fixed time
    msleep(500);
    //Set speed
    SetMotorSpeed(-100);
    //Wait fixed time
    msleep(500);
    //Set speed
    SetMotorSpeed(25);
    //Wait fixed time
    msleep(500);
    SetMotorSpeed(75);
    //Wait fixed time
    msleep(500);
    //Stop motor and wait
    SetMotorSpeed(0);
    msleep(100);
    //Get Measurements
    _MotorTuning->StopMeasuring();    
}

void MotorTuningController::SetMotorSpeed(short speed) {
    _Motor->SetMotorLeftSpeed(speed);
    _Motor->SetMotorRightSpeed(speed);
}

void MotorTuningController::SaveMeasureToFile(std::string filename) {
   std::ofstream out(filename.c_str()  );
   if( !out )
   {
      std::cout << "Couldn't open file."  << std::endl;
      return;
   }

   out << "Target, Error\n"; 
   int nrMeasurement = _MotorTuning->GetNrOfMeasurement();
   for(int i=0; i< nrMeasurement; i++)
   {
       out << _MotorTuning->GetTarget();
       out << ", " << _MotorTuning->GetError() << "\n";
       _MotorTuning->NextMeasure();
   }
   out.close();
}
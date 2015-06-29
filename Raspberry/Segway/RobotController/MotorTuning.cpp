#include "MotorTuning.h"

MotorTuning::MotorTuning(HardwareController* controller) {
    _Controller = controller;
    _NrOfMeasurement = 250;
}

MotorTuning::~MotorTuning() {
}

void MotorTuning::StartMeasuring() {
    _Controller->SendCommand(MotorCommandType::Reset_Logger, 0);
    _Controller->SendCommand(MotorCommandType::Set_Logging_State, 1);
}

void MotorTuning::StopMeasuring() {
    _Controller->SendCommand(MotorCommandType::Set_Logging_State, 0);
}

short MotorTuning::GetError() {
    return _Controller->SendCommand(MotorCommandType::Get_Logging_Error, 0);
}

short MotorTuning::GetTarget() {
    return _Controller->SendCommand(MotorCommandType::Get_Logging_Target, 0);
}

void MotorTuning::NextMeasure() {
    _Controller->SendCommand(MotorCommandType::Next_Logging, 0);
}

int MotorTuning::GetNrOfMeasurement() {
    return _NrOfMeasurement;
}
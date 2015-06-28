#include "MotorTuning.h"

MotorTuning::MotorTuning(HardwareController* controller) {
    _Controller = controller;
    _NrOfMeasurement = 250;
}

MotorTuning::~MotorTuning() {
}

void MotorTuning::StartMeasuring() {
    _Controller->SendCommand(CommandType::Reset_Logger, 0);
    _Controller->SendCommand(CommandType::Set_Logging_State, 1);
}

void MotorTuning::StopMeasuring() {
    _Controller->SendCommand(CommandType::Set_Logging_State, 0);
}

short MotorTuning::GetError() {
    return _Controller->SendCommand(CommandType::Get_Logging_Error, 0);
}

short MotorTuning::GetTarget() {
    return _Controller->SendCommand(CommandType::Get_Logging_Target, 0);
}

void MotorTuning::NextMeasure() {
    _Controller->SendCommand(CommandType::Next_Logging, 0);
}

int MotorTuning::GetNrOfMeasurement() {
    return _NrOfMeasurement;
}
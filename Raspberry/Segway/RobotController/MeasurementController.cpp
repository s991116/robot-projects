#include "MeasurementController.h"

MeasurementController::MeasurementController(HardwareController* controller) {
    _Controller = controller;
    _NrOfMeasurement = 250;
}

MeasurementController::~MeasurementController() {
}

void MeasurementController::StartMeasuring() {
    _Controller->SendCommand(CommandType::Set_Logging_State, 0);
}

void MeasurementController::StopMeasuring() {
    _Controller->SendCommand(CommandType::Set_Logging_State, 1);
}

short MeasurementController::GetError() {
    return _Controller->SendCommand(CommandType::Get_Logging_Value1, 0);
}

short MeasurementController::GetTarget() {
    return _Controller->SendCommand(CommandType::Get_Logging_Value2, 0);
}

void MeasurementController::NextMeasure() {
    _Controller->SendCommand(CommandType::Next_Logging, 0);
}

int MeasurementController::GetNrOfMeasurement() {
    return _NrOfMeasurement;
}
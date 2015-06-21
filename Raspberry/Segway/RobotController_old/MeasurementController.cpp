#include "MeasurementController.h"

MeasurementController::MeasurementController(HardwareController* controller) {
    _Controller = controller;
    _NrOfMeasurement = 500;
}

MeasurementController::~MeasurementController() {
}

void MeasurementController::StartMeasuring() {
    _Controller->SendCommand(CommandType::Set_Logging_State, 0);
}

void MeasurementController::StopMeasuring() {
    _Controller->SendCommand(CommandType::Set_Logging_State, 1);
}

short MeasurementController::GetNextMeasure() {
    return _Controller->SendCommand(CommandType::Get_Logging_Value, 0);
}

int MeasurementController::GetNrOfMeasurement() {
    return _NrOfMeasurement;
}
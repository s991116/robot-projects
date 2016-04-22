#include "Navigate.h"

Navigate::Navigate(SerialCommandProtocol* serialProtocol) {
    _SerialProtocol = serialProtocol;
}

void Navigate::ForwardSpeed(short speed) {
    char speedByte = speed + 127;
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeByte::SEGWAY_SPEED, speedByte);
}

void Navigate::TurnSpeed(short turn) {
    char turnByte = turn + 127;
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeByte::SEGWAY_TURN, turnByte);    
}

short Navigate::GetForwardSpeed() {
    short speedByte = _SerialProtocol->getByteData(HardwareControllerCommandTypeByte::SEGWAY_SPEED);
    return speedByte - 127;
}

short Navigate::GetTurnSpeed() {
    short turnByte = _SerialProtocol->getByteData(HardwareControllerCommandTypeByte::SEGWAY_TURN);
    return turnByte - 127;
}

void Navigate::EnableSegway() {
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeByte::SEGWAY_ENABLED, true);    
}

void Navigate::DisableSegway() {
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeByte::SEGWAY_ENABLED, false);    
}

void Navigate::SetPID_P(short p){
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeShort::PID_SPEED_P, p);    
}

void Navigate::SetPID_I(short i){
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeShort::PID_SPEED_I, i);    
}

void Navigate::SetPID_D(short d){
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeShort::PID_SPEED_D, d);    
}

short Navigate::GetPID_P() {
    return _SerialProtocol->getShortData(HardwareControllerCommandTypeShort::PID_SPEED_P);        
}

short Navigate::GetPID_I() {
    return _SerialProtocol->getShortData(HardwareControllerCommandTypeShort::PID_SPEED_I);        
}

short Navigate::GetPID_D() {
    return _SerialProtocol->getShortData(HardwareControllerCommandTypeShort::PID_SPEED_D);        
}

void Navigate::SetPIDLimit(short limit) {
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeShort::SPEED_PID_LIMIT, limit);
}

short Navigate::GetPIDLimit() {
    return _SerialProtocol->getShortData(HardwareControllerCommandTypeShort::SPEED_PID_LIMIT);        
}

void Navigate::SetSpeedCorrLimit(short limit) {
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeShort::SPEED_CORR_LIMIT, limit);
}

short Navigate::GetSpeedCorrLimit() {
    return _SerialProtocol->getShortData(HardwareControllerCommandTypeShort::SPEED_CORR_LIMIT);        
}

Navigate::~Navigate() {
}


#include "Navigate.h"
#include "CommandType.h"

Navigate::Navigate(MessageDataProtocol* serialProtocol) {
    _SerialProtocol = serialProtocol;
}

void Navigate::ForwardSpeed(short speed) {
    char speedByte = speed + 127;
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeByte::SEGWAY_SPEED, speedByte);
}

void Navigate::TurnSpeed(short turn) {
    char turnByte = turn + 127;
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeByte::SEGWAY_TURN, turnByte);    
}

short Navigate::GetForwardSpeed() {
    short speedByte = _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeByte::SEGWAY_SPEED);
    return speedByte - 127;
}

short Navigate::GetTurnSpeed() {
    short turnByte = _SerialProtocol->RequestCharData((char)HardwareControllerCommandTypeByte::SEGWAY_TURN);
    return turnByte - 127;
}

void Navigate::EnableSegway() {
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeByte::SEGWAY_ENABLED, true);    
}

void Navigate::DisableSegway() {
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeByte::SEGWAY_ENABLED, false);    
}

void Navigate::SetPID_P(short p){
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeShort::PID_SPEED_P, p);    
}

void Navigate::SetPID_I(short i){
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeShort::PID_SPEED_I, i);    
}

void Navigate::SetPID_D(short d){
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeShort::PID_SPEED_D, d);    
}

short Navigate::GetPID_P() {
    return _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeShort::PID_SPEED_P);        
}

short Navigate::GetPID_I() {
    return _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeShort::PID_SPEED_I);        
}

short Navigate::GetPID_D() {
    return _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeShort::PID_SPEED_D);        
}

void Navigate::SetPIDLimit(short limit) {
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeShort::SPEED_PID_LIMIT, limit);
}

short Navigate::GetPIDLimit() {
    return _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeShort::SPEED_PID_LIMIT);        
}

void Navigate::SetSpeedCorrLimit(short limit) {
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeShort::SPEED_CORR_LIMIT, limit);
}

short Navigate::GetSpeedCorrLimit() {
    return _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeShort::SPEED_CORR_LIMIT);        
}

Navigate::~Navigate() {
}
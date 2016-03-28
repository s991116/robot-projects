#include "Gyro.h"

Gyro::Gyro(SerialCommandProtocol* serialProtocol) {
    _SerialProtocol = serialProtocol;
}

short Gyro::GetAngle() {
    return _SerialProtocol->getShortData(HardwareControllerCommandTypeShort::ANGLE_OFFSET);
}

short Gyro::GetAnglePid_p() {
    return _SerialProtocol->getShortData(HardwareControllerCommandTypeShort::PID_GYRO_P);
}

short Gyro::GetAnglePid_i() {
    return _SerialProtocol->getShortData(HardwareControllerCommandTypeShort::PID_GYRO_I);
}

short Gyro::GetAnglePid_d() {
    return _SerialProtocol->getShortData(HardwareControllerCommandTypeShort::PID_GYRO_D);
}

void Gyro::SetAnglePid_p(short p) {
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeShort::PID_GYRO_P, p);
}

void Gyro::SetAnglePid_i(short i) {
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeShort::PID_GYRO_I, i);
}

void Gyro::SetAnglePid_d(short d) {
    _SerialProtocol->sendCommandAndData(HardwareControllerCommandTypeShort::PID_GYRO_D, d);
}

Gyro::~Gyro() {
}
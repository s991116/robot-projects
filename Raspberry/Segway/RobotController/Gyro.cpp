#include "Gyro.h"
#include "CommandType.h"

Gyro::Gyro(MessageDataProtocol* serialProtocol) {
    _SerialProtocol = serialProtocol;
}

short Gyro::GetAngle() {
    return _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeShort::ANGLE_OFFSET);
}

short Gyro::GetAnglePid_p() {
    return _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeShort::PID_GYRO_P);
}

short Gyro::GetAnglePid_i() {
    return _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeShort::PID_GYRO_I);
}

short Gyro::GetAnglePid_d() {
    return _SerialProtocol->RequestShortData((char)HardwareControllerCommandTypeShort::PID_GYRO_D);
}

void Gyro::SetAnglePid_p(short p) {
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeShort::PID_GYRO_P, p);
}

void Gyro::SetAnglePid_i(short i) {
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeShort::PID_GYRO_I, i);
}

void Gyro::SetAnglePid_d(short d) {
    _SerialProtocol->SendData((char)HardwareControllerCommandTypeShort::PID_GYRO_D, d);
}

Gyro::~Gyro() {
}
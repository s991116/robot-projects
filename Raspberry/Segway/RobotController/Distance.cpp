#include "Distance.h"
#include "CommandType.h"

Distance::Distance(MessageDataProtocol* serialProtocol) {
    _SerialProtocol = serialProtocol;
}

int Distance::GetDistance() {
    short data[1];
    _SerialProtocol->RequestData((char)HardwareControllerCommandTypeShort::DISTANCE, 0,data);
    return data[1];
}

void Distance::ResetDistance() {
    char data[1];
    _SerialProtocol->SendData((char)HardwareControllerCommand::RESET_DISTANCE, 0,data);
}

Distance::~Distance() {
}


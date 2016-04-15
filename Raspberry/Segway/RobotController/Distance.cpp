#include "Distance.h"

Distance::Distance(SerialCommandProtocol* serialProtocol) {
    _SerialProtocol = serialProtocol;
}

int Distance::GetDistance() {
    return _SerialProtocol->getShortSignedData(HardwareControllerCommandTypeShort::DISTANCE);
}

void Distance::ResetDistance() {
  _SerialProtocol->sendCommand(HardwareControllerCommand::RESET_DISTANCE);
}

Distance::~Distance() {
}


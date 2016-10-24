#include "SerialConnectorMock.h"

SerialConnectorMock::SerialConnectorMock() {
    _Com1 = new SerialComMock();
    _Com2 = new SerialComMock();
    
    _Com1->SetOppositeSerial(_Com2);
    _Com2->SetOppositeSerial(_Com1);

}

SerialCom* SerialConnectorMock::GetSerialCom1() {
    return _Com1;
}

SerialCom* SerialConnectorMock::GetSerialCom2() {
    return _Com2;
}

SerialConnectorMock::~SerialConnectorMock() {
}


#include "DataPackets.h"

DataPackets::DataPackets(SerialCom* serialCom) {
    _SerialCom = serialCom;
}

bool DataPackets::PacketAvailable() {
    while (_SerialCom->DataAvailable()) {
        if (_SerialCom->PeekNextChar() >> 7 == 1)
            return true;
        else
            _SerialCom->ReadNextChar();
    }
    return false;
}

char* DataPackets::GetCharDataBuffer() {
    return _DataChar;
}

short* DataPackets::GetShortDataBuffer() {
    return _DataShort;
}

void DataPackets::FillSerialData(char serialData[]) {
    if (_Direction == PacketDirection::SendData || _Direction == PacketDirection::ReplyData) {
        if (_Type == PacketType::Char) {
            for (int i = 0; i < _Length; i++) {
                serialData[i * 2 + 1] = _DataChar[i] & 0x0F;
                serialData[i * 2 + 2] = (_DataChar[i] >> 4) & 0x0F;
            }
            _SerialLength = _Length * 2 + 1;
        }
        if (_Type == PacketType::Short) {
            for (int i = 0; i < _Length; i++) {
                serialData[i * 4 + 1] = _DataShort[i] & 0x0F;
                serialData[i * 4 + 2] = (_DataShort[i] >> 4) & 0x0F;
                serialData[i * 4 + 3] = (_DataShort[i] >> 8) & 0x0F;
                serialData[i * 4 + 4] = (_DataShort[i] >> 12) & 0x0F;
            }
            _SerialLength = _Length * 4 + 1;
        }
    }
    if (_Direction == PacketDirection::RequestData) {
        _SerialLength = 3;
    }

    serialData[0] = _CommandId + 0x80;
    serialData[1] |= (char) (_Direction) << 5;
    serialData[1] |= (char) (_Type) << 4;
    serialData[2] |= (_Length - 1) << 4;
}

int DataPackets::GetSerialDataLength() {
    return _SerialLength;
}

void DataPackets::SendData() {
    char serialData[100];
    FillSerialData(serialData);
    for (int i = 0; i < GetSerialDataLength(); i++)
        _SerialCom->WriteChar(serialData[i]);
}

void DataPackets::SendReply() {
    this->_Direction = PacketDirection::ReplyData;
    SendData();
}

void DataPackets::GetData() {
    char serialData[100];
    int index = 0;
    
    serialData[0] = GetSerialData();
    serialData[1] = GetSerialData();
    serialData[2] = GetSerialData();

    _CommandId = serialData[0] - 0x80;
    _Length = ((serialData[2] >> 4) & 0x07) + 1;
    _Type = (PacketType::type) ((serialData[1] >> 4) & 0x01);
    _Direction = (PacketDirection::type) ((serialData[1] >> 5) & 0x03);
    
    int serialLength = CalcSerialLength(_Length, _Type, _Direction);
    for (int index = 3; index < serialLength; index++) {
        serialData[index] = GetSerialData();
    }
    GetSerialData(serialData);
}

int DataPackets::CalcSerialLength(char length, PacketType::type type, PacketDirection::type direction) {
    if(direction == PacketDirection::RequestData)
        return 3;
    
    switch(type)
    {
        case PacketType::Char:
            return length*2+1;
            
        case PacketType::Short:
            return length*4+1;
    }
}

int DataPackets::GetSerialData() {
    while(_SerialCom->DataAvailable() < 1);
    
    return _SerialCom->ReadNextChar();
}

void DataPackets::SetRequest(char commandId, char length, short data[]) {
    _CommandId = commandId;
    _Length = length;
    _Type = PacketType::Short;
    _Direction = PacketDirection::SendData;

    for (int i = 0; i < _Length; i++)
        _DataShort[i] = data[i];
}

void DataPackets::SetRequest(char commandId, char length, char data[]) {
    _CommandId = commandId;
    _Length = length;
    _Type = PacketType::Char;
    _Direction = PacketDirection::SendData;

    for (int i = 0; i < _Length; i++)
        _DataChar[i] = data[i];
}

void DataPackets::GetRequest(char commandId, char length, PacketType::type type) {
    _CommandId = commandId;
    _Length = length;
    _Type = type;
    _Direction = PacketDirection::RequestData;
}

void DataPackets::GetSerialData(char serialData[]) {

    if (_Direction == PacketDirection::SendData || _Direction == PacketDirection::ReplyData) {
        if (_Type == PacketType::Char) {
            for (int i = 0; i < _Length; i++) {
                _DataChar[i] = (serialData[2 * i + 1] & 0x0F) + ((serialData[2 * i + 2] & 0x0F) << 4);
            }
        }

        if (_Type == PacketType::Short) {
            for (int i = 0; i < _Length; i++) {
                short d1 = (serialData[4 * i + 1] & 0x0F) + ((serialData[4 * i + 2] & 0x0F) << 4);
                short d2 = (serialData[4 * i + 3] & 0x0F) + ((serialData[4 * i + 4] & 0x0F) << 4);
                _DataShort[i] = d1 + (d2 << 8);
            }
        }
    }
}

void DataPackets::FillData(short serialData[]) {
    for (int i = 0; i < _Length; i++) {
        serialData[i] = _DataShort[i];
    }
}

void DataPackets::FillData(char serialData[]) {
    for (int i = 0; i < _Length; i++) {
        serialData[i] = _DataChar[i];
    }
}

char DataPackets::GetCommandId() {
    return _CommandId;
}

char DataPackets::GetLength() {
    return _Length;
}

PacketType::type DataPackets::GetType() {
    return _Type;
}

PacketDirection::type DataPackets::GetDirection() {
    return _Direction;
}

DataPackets::~DataPackets() {
}
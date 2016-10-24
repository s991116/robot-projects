#include "MessageDataProtocol.h"

MessageDataProtocol::MessageDataProtocol(DataPackets* dataPackets, DataHandlerInterface* dataHandler) {
    _DataPackets = dataPackets;
    _DataHandler = dataHandler;
}

void MessageDataProtocol::Update() {
    if (_DataPackets->PacketAvailable()) {
        _DataPackets->GetData();

        switch (_DataPackets->GetDirection()) {
            case PacketDirection::SendData:
                if (_DataPackets->GetType() == PacketType::Char)
                    _DataHandler->HandleData(_DataPackets->GetCommandId(), _DataPackets->GetLength(), _DataPackets->GetCharDataBuffer());
                if (_DataPackets->GetType() == PacketType::Short)
                    _DataHandler->HandleData(_DataPackets->GetCommandId(), _DataPackets->GetLength(), _DataPackets->GetShortDataBuffer());
                break;

            case PacketDirection::RequestData:
                if (_DataPackets->GetType() == PacketType::Char) {
                    _DataHandler->HandleReply(_DataPackets->GetCommandId(), _DataPackets->GetLength(), _DataPackets->GetCharDataBuffer());
                    _DataPackets->SendReply();
                }
                if (_DataPackets->GetType() == PacketType::Short) {
                    _DataHandler->HandleReply(_DataPackets->GetCommandId(), _DataPackets->GetLength(), _DataPackets->GetShortDataBuffer());
                    _DataPackets->SendReply();
                }
                break;

            case PacketDirection::ReplyData:
                if (_DataPackets->GetType() == PacketType::Char) {
                    char* data = _DataPackets->GetCharDataBuffer();
                    for(int i=0; i< _DataPackets->GetLength(); i++ )
                      _ReplyDataChar[i] = data[i];
                }
                if (_DataPackets->GetType() == PacketType::Short) {
                    short* data = _DataPackets->GetShortDataBuffer();
                    for(int i=0; i< _DataPackets->GetLength(); i++ )
                      _ReplyDataShort[i] = data[i];
                }
                _ReplyReceived = true;
                break;
        }
    }
}

void MessageDataProtocol::SendData(char commandId, bool data) {
    SendData(commandId, (char) data);
}

void MessageDataProtocol::SendData(char commandId, char data) {
    char dataArray[1] = {data};
    SendData(commandId,1,dataArray);
}

void MessageDataProtocol::SendData(char commandId, char length, char data[]) {
    _DataPackets->SetRequest(commandId, length, data);
    _DataPackets->SendData();
}

void MessageDataProtocol::SendData(char commandId, short data) {
    short dataArray[1] = {data};
    SendData(commandId,1,dataArray);
}

void MessageDataProtocol::SendData(char commandId, char length, short data[]) {
    _DataPackets->SetRequest(commandId, length, data);
    _DataPackets->SendData();
}

char MessageDataProtocol::RequestCharData(char commandId) {
    char data[1];
    this->RequestData(commandId,1, data);
    return data[0];
}

short MessageDataProtocol::RequestShortData(char commandId) {
    short data[1];
    this->RequestData(commandId,1, data);
    return data[0];    
}

void MessageDataProtocol::RequestData(char commandId, char length, char data[]) {
    _DataPackets->GetRequest(commandId, length, PacketType::Char);
    _DataPackets->SendData();
    _ReplyReceived = false;
    
    while(!_ReplyReceived)
    {
        Update();
    }
    for(int i=0; i< _DataPackets->GetLength(); i++ )
        data[i] = _ReplyDataChar[i];

}

void MessageDataProtocol::RequestData(char commandId, char length, short data[]) {
    _DataPackets->GetRequest(commandId, length, PacketType::Short);
    _DataPackets->SendData();
    _ReplyReceived = false;
    
    while(!_ReplyReceived)
    {
        Update();
    }
    for(int i=0; i< _DataPackets->GetLength(); i++ )
        data[i] = _ReplyDataShort[i];

}

MessageDataProtocol::~MessageDataProtocol() {
}
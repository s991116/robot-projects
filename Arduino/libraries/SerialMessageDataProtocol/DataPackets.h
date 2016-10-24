#ifndef DATAPACKETS_H
#define	DATAPACKETS_H

#include "SerialCom.h"

//enum class PacketDirection { SendData = 0, RequestData = 1, ReplyData = 2};
//enum class PacketType {Char = 0, Short = 1};

struct PacketDirection { enum type { SendData = 0, RequestData = 1, ReplyData = 2 }; };
struct PacketType { enum type {Char = 0, Short = 1}; };

class DataPackets {
public:
    DataPackets(SerialCom* serialCom);
    void SetRequest(char commandId, char length, char data[]);
    void SetRequest(char commandId, char length, short data[]);
    void GetRequest(char commandId, char length, PacketType::type type);
    bool PacketAvailable();
    char GetCommandId();
    char GetLength();
    char* GetCharDataBuffer();
    short* GetShortDataBuffer();    
    PacketType::type GetType();
    PacketDirection::type GetDirection();

    void SendData();
    void SendReply();
    void GetData();

    virtual ~DataPackets();
private:
    int GetSerialDataLength(); 
    void FillSerialData(char serialData[]);
    void GetSerialData(char serialData[]);
    void FillData(char serialData[]);
    void FillData(short serialData[]);
    int CalcSerialLength(char length, PacketType::type type, PacketDirection::type direction);
    int GetSerialData();
    char _CommandId;
    PacketDirection::type _Direction;
    PacketType::type _Type;
    char _Length;
    short _DataShort[15];
    char  _DataChar[15];
    int _SerialLength;
    SerialCom* _SerialCom;
};

#endif	/* DATAPACKETS_H */


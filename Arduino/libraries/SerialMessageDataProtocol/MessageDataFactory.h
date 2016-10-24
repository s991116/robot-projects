#ifdef ARDUINO

#ifndef MESSAGEDATAFACTORY_H
#define	MESSAGEDATAFACTORY_H

#include "ArduinoSerial.h"
#include "ArduinoDataHandler.h"
#include "MessageDataProtocol.h"

class MessageDataFactory{
	public:
    static MessageDataProtocol Create(Stream* serial, ArduinoDataHandler* dataHandler) {
        SerialCom* arduinoSerial = new ArduinoSerial(serial);
        DataPackets* dataPacket= new DataPackets(arduinoSerial);
		
        return MessageDataProtocol(dataPacket, dataHandler);
    }
};

#endif	/* MESSAGEDATAFACTORY_H */

#endif //ARDUINO
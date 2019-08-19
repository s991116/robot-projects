#include <Arduino.h>
//#include <Serial.h>

class SerialCommunication {
	public:
	    SerialCommunication(HardwareSerial *serial);
        void ReceiveData();
        byte GetNavigation();
        byte GetReceivedCmd();
        byte GetReceivedData();
        void SendData(byte data);
 

	private:
	    HardwareSerial *uart;
        byte _recivedCmd;
        byte _navigationReceived;
        byte _navigationReceiveCounter;
        byte _receivedData;
        bool _waitingForData;
};
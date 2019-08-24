#include <Arduino.h>
//#include <Serial.h>

typedef void (**receiveFunctionsP)(unsigned char);
typedef void (*receiveFunctionsArray)(unsigned char);

typedef unsigned char (**transmitFunctionsP)(void);
typedef unsigned char (*transmitFunctionsArray)(void);

class SerialCommunication {
	public:
	    SerialCommunication(HardwareSerial *serial, receiveFunctionsP receiveFunctions, transmitFunctionsP transmitFunctions);
        void Initialize();
		void HandleCommunication(); 

	private:
	    HardwareSerial *uart;
        receiveFunctionsP _receiveFunctions;
        transmitFunctionsP _transmitFunctions;
};
#include <Arduino.h>

typedef void (**receiveFunctionsP)(unsigned char);
typedef void (*receiveFunctionsArray)(unsigned char);

typedef unsigned char (**transmitFunctionsP)(void);
typedef unsigned char (*transmitFunctionsArray)(void);

typedef void (*navigationFunctionP)(byte);

class SerialCommunication {
	public:
	    SerialCommunication(HardwareSerial *serial, receiveFunctionsP receiveFunctions, transmitFunctionsP transmitFunctions, navigationFunctionP navigationFunction);
        void Initialize();
		void HandleCommunication(); 

	private:
	    HardwareSerial *uart;
		enum State { getCmd, handleCmd, callFunction, respond};
		State _state;
		unsigned char _cmdType;
		unsigned char _receivedData;
		unsigned char _data;
		unsigned char _cmd;
        receiveFunctionsP _receiveFunctions;
        transmitFunctionsP _transmitFunctions;
		navigationFunctionP _navigationFunction;
};
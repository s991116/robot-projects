#include "IrRobot.h"

IrRobot::IrRobot(int pin) : irrecv(4) {
	//irrecv = IRrecv(pin);
	irrecv.enableIRIn();
}

long IrRobot::GetKeyCode() {
  long result = 0;
  if (irrecv.decode(&results)) {
    result = results.value;
    irrecv.resume(); // Receive the next value    
  }
  return result;
/*
  if (irrecv.decode(&results))
  {
	_lastKey = results.value;

    if(results.value != IR_KEY_REPEATED)
    {
      _lastKey = results.value;
	}
	
	irrecv.resume(); 
	
    return _lastKey;
  }
  return IR_KEY_NONE;
  */
}

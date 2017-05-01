#ifndef IRROBOT_H
#define IRROBOT_H

#include "IRremote.h"
#include "IrRobotKeyMap.h"

class IrRobot{
  public:
    IrRobot(int pin);
	long GetKeyCode();
	
  private:
    IRrecv irrecv;
    decode_results results;
	long _lastKey;
};

#endif //IRROBOT_H
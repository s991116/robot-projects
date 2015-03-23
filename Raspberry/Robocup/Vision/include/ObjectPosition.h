#ifndef OBJECTPOSITION_H 
#define OBJECTPOSITION_H

#include <Position.h>

class ObjectPosition {
public:
  ObjectPosition();
  bool Detected;
  Position* Center;
  Position* Corner1;
  Position* Corner2;
};

#endif //OBJECTPOSITION_H
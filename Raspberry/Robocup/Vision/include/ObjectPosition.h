#ifndef OBJECTPOSITION_H 
#define OBJECTPOSITION_H

#include <Position.h>
#include <string>

class ObjectPosition {
public:
  ObjectPosition();
  bool WithinImage();
  std::string Print();
  
  bool Detected;
  Position* Center;
  Position* Corner1;
  Position* Corner2;
};

#endif //OBJECTPOSITION_H
#include <nan.h>
#include "RobotWrapper.h"

void Init(v8::Local<v8::Object> exports) {
  RobotWrapper::Init(exports);
}

NODE_MODULE(robot, Init)
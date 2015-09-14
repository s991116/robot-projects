#ifndef ROBOTWRAPPER_H
#define ROBOTWRAPPER_H

#include <nan.h>
#include <Robot.h>

class RobotWrapper : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit RobotWrapper(Robot* robot);
  ~RobotWrapper();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void GetValue(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void SetValue(const Nan::FunctionCallbackInfo<v8::Value>& info);  
  static void BalanceEnabled(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static Nan::Persistent<v8::Function> constructor;
  
  int _Value;
  Robot * _Robot;
};

#endif //ROBOTWRAPPER

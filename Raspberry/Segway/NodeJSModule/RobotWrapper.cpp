#include "RobotWrapper.h"

Nan::Persistent<v8::Function> RobotWrapper::constructor;

RobotWrapper::RobotWrapper(Robot* robot) {
	_Robot = robot;
}

RobotWrapper::~RobotWrapper() {
}

void RobotWrapper::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("RobotWrapper").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "getvalue", GetValue);
  Nan::SetPrototypeMethod(tpl, "setvalue", SetValue);
  Nan::SetPrototypeMethod(tpl, "BalanceEnabled", BalanceEnabled);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("RobotWrapper").ToLocalChecked(), tpl->GetFunction());
}

void RobotWrapper::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Robot* robot = new Robot();

  if (info.IsConstructCall()) {
    // Invoked as constructor: `new RobotWrapper(...)`
    RobotWrapper* obj = new RobotWrapper(robot);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `RobotWrapper(...)`, turn into construct call.
    const int argc = 0;
    v8::Local<v8::Value> argv[argc];
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void RobotWrapper::GetValue(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  RobotWrapper* obj = ObjectWrap::Unwrap<RobotWrapper>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->_Value));
}

void RobotWrapper::SetValue(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  RobotWrapper* obj = ObjectWrap::Unwrap<RobotWrapper>(info.Holder());
  int value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
  obj->_Value = value;
  obj->_Robot->_Motor->SetMotorLeftSpeed(value);
  obj->_Robot->_Motor->SetMotorRightSpeed(value);
}

void RobotWrapper::BalanceEnabled(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  RobotWrapper* obj = ObjectWrap::Unwrap<RobotWrapper>(info.Holder());
  int value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
  
  obj->_Robot->_Gyro->SetPidState(value);
}
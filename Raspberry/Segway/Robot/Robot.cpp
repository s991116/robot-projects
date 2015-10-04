#include "Robot.h"

Robot::Robot() {
  _ComPort = new ComPort();
  _HwCtrl = new HardwareController(_ComPort);
  _Motor = new Motor(_HwCtrl);
  _MotorTuning = new MotorTuning(_HwCtrl);
  _Gyro = new Gyro(_HwCtrl);
  _Servo = new Servo(_HwCtrl);
  _Camera = new PiCamera();
  _FaceDetection = new FaceDetection();
  _CameraSensor = new CameraSensor(_Camera, _FaceDetection, _Servo);    
}

Robot::~Robot() {
}
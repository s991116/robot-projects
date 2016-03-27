#include "Robot.h"
#include "EmptyLog.h"

Robot::Robot() {
  _ComPort = new ComPort();
  _ComStream = new ComStream(_ComPort);
  _CommunicationHandler = new CommunicationHandler();
  _SerialProtocol = new SerialCommandProtocol(_ComStream, _CommunicationHandler);

  _HwCtrl = new HardwareController(_ComPort);
  _Motor = new Motor(_HwCtrl);
  _MotorTuning = new MotorTuning(_HwCtrl);
  _Gyro = new Gyro(_HwCtrl);
  _Servo = new Servo(_HwCtrl);
  _Camera = new PiCamera();
  _FaceDetection = new FaceDetection();
  //cv::Rect bottomLineRoi(0, 40, 320, 2);
  //_Log = new EmptyLog();

  //cv::Rect topRoi(0, 40, 320, 2);
  //_BottomLineDetectSetting = new LineDetectSetting(topRoi, 10, 300, LineDetectSetting::CENTER, LineDetectSetting::VERTICAL, false);
  //_BottomLineDetect = new LineDetect(_BottomLineDetectSetting, _Log);

  //_LineDetectSetting = new LineDetectSetting();
  _CameraSensor = new CameraSensor(_Camera, _FaceDetection, _Servo);    
}

Robot::~Robot() {
}
#include "Robot.h"
#include "EmptyLog.h"

Robot::Robot() {
  _ComPort = new ComPort();
  _ComStream = new ComStream(_ComPort);
  _CommunicationHandler = new CommunicationHandler();
  _SerialProtocol = new SerialCommandProtocol(_ComStream, _CommunicationHandler);
  _Navigate = new Navigate(_SerialProtocol);
  _Motor = new Motor(_SerialProtocol);
  _Gyro = new Gyro(_SerialProtocol);
  _Servo = new Servo(_SerialProtocol);
  _Camera = new PiCamera();
  _FaceDetection = new FaceDetection();
  _CameraSensor = new CameraSensor(_Camera, _FaceDetection, _Servo);    
}

Robot::~Robot() {
}
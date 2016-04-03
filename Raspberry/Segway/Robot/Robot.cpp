#include "Robot.h"
#include "EmptyLog.h"
#include "CommandScript.h"
#include "Setting.h"
#include "Command.h"

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
  _LineDetectSetting = new LineDetectSetting();  
  Logging* logging = new EmptyLog();
  _LineDetect = new LineDetect(_LineDetectSetting, logging);
  _CameraSensor = new CameraSensor(_Camera, _FaceDetection, _LineDetect, _Servo);
  std::map<std::string, int> parseCommands;
  ParseCommandLine* parseCommandLine = new ParseCommandLine(parseCommands);
  map<string, Command*> commands;
  map<string, Setting*> settings;
  map<string, SensorInfo*> sensors;
  
  _CommandScript = new CommandScript(parseCommandLine, commands, settings, sensors);
}

Robot::~Robot() {
}
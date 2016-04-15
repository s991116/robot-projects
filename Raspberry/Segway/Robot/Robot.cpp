#include "Robot.h"
#include "ProxyLog.h"
#include "EmptyLog.h"
#include "FileLogger.h"
#include "ConsoleLog.h"
#include "CommandScript.h"
#include "SegwayCommand.h"
#include "FollowLineCommand.h"
#include "Setting.h"
#include "Command.h"
#include "CheckSwitch.h"
#include "TimeCheck.h"
#include "PressKeyInfo.h"

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
  _DetectFace = new DetectFace();
  _LineDetectSetting = new LineDetectSetting();  
  _LineDetect = new LineDetect(_LineDetectSetting, new EmptyLog());//new FileLogger("Log.txt"));
  _CameraSensor = new CameraSensor(_Camera, _DetectFace, _LineDetect, _Servo);
  std::map<std::string, int> parseCommands;
  ParseCommandLine* parseCommandLine = new ParseCommandLine(parseCommands);
  TimeCheck* timeCheck = new TimeCheck();
  PressKeyInfo* pressKeyInfo = new PressKeyInfo();
  CheckSwitch* checkSwitch = new CheckSwitch(timeCheck, pressKeyInfo);
  FollowLineCommand* followLine = new FollowLineCommand(checkSwitch, _CameraSensor, _Navigate, new EmptyLog());//new FileLogger("Log.txt"));
  
  map<string, Command*> commands;
  map<string, Setting*> settings;
  map<string, SensorInfo*> sensors;
  
  settings["LINEDETECTSETTING"] = _LineDetectSetting;
  settings["TIMER"] = timeCheck;
  settings["CHECK"] = checkSwitch;
  settings["FOLLOWLINE"] = followLine;

  commands["DELAY"] = new DelayCommand();
  commands["KEYPRESS"] = new KeyPressCommand();
  commands["SEGWAY"] = new SegwayCommand(_Navigate); 
  commands["FOLLOWLINE"] = followLine;
  
  
  sensors["HEAD"] = _CameraSensor;
  
  _CommandScript = new CommandScript(parseCommandLine, commands, settings, sensors);
}

Robot::~Robot() {
}
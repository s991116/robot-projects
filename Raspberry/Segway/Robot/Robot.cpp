#include "Robot.h"
#include "ProxyLog.h"
#include "EmptyLog.h"
#include "FileLogger.h"
#include "ConsoleLog.h"
#include "CommandScript.h"
#include "SegwayCommand.h"
#include "FollowLineCommand.h"
#include "FollowLineAndWaitCommand.h"
#include "NavigateCommand.h"
#include "WaitCommand.h"
#include "CalibrateGyro.h"
#include "Setting.h"
#include "Command.h"
#include "CheckSwitch.h"
#include "TimeCheck.h"
#include "DistanceCheck.h"
#include "PressKeyInfo.h"
#include "LineDetected.h"

#include "DataPackets.h"
#include "SerialCom.h"
#include "SerialComRaspi.h"

Robot::Robot() {
  _ComPort = new ComPort();
  _ComStream = new ComStream(_ComPort);
  _CommunicationHandler = new CommunicationHandler();
  SerialComRaspi* serialCom = new SerialComRaspi(_ComStream);
  DataPackets* dataPackets = new DataPackets(serialCom);
  _SerialProtocol = new MessageDataProtocol(dataPackets, _CommunicationHandler);
  _Navigate = new Navigate(_SerialProtocol);
  _Motor = new Motor(_SerialProtocol);
  _Gyro = new Gyro(_SerialProtocol);
  _Servo = new Servo(_SerialProtocol);
  _Camera = new PiCamera();
  _LineDetectSetting = new LineDetectSetting();  
  _LineDetect = new LineDetect(_LineDetectSetting, new EmptyLog());//new FileLogger("Log.txt"));
  _SensorLineDetectSetting = new LineDetectSetting();  
  _SensorLineDetect = new LineDetect(_SensorLineDetectSetting, new EmptyLog());//new FileLogger("Log.txt"));

  //  _LineDetect = new LineDetect(_LineDetectSetting, new FileLogger("Log.txt"));
  _CameraSensor = new CameraSensor(_Camera, _LineDetect, _SensorLineDetect, _Servo);
  
  std::map<std::string, int> parseCommands;
  ParseCommandLine* parseCommandLine = new ParseCommandLine(parseCommands);
  TimeCheck* timeCheck = new TimeCheck();
  _Distance = new Distance(_SerialProtocol);
  DistanceCheck* distanceCheck = new DistanceCheck(_Distance);
  PressKeyInfo* pressKeyInfo = new PressKeyInfo();
  LineDetected* lineDetected = new LineDetected(_CameraSensor);
  CheckSwitch* checkSwitch = new CheckSwitch(timeCheck, pressKeyInfo, distanceCheck, lineDetected);
  FollowLineCommand* followLine = new FollowLineCommand(checkSwitch, _CameraSensor, _Navigate, new EmptyLog());//new FileLogger("Log.txt"));
  FollowLineAndWaitCommand* followLineWait = new FollowLineAndWaitCommand(checkSwitch, _CameraSensor, _Navigate, new EmptyLog());//new FileLogger("Log.txt"));  
  NavigateCommand* navigateCommand = new NavigateCommand(_Navigate);
  CalibrateGyro* calibrateGyro = new CalibrateGyro(_Navigate, _Gyro);
  
  map<string, Command*> commands;
  map<string, Setting*> settings;
  map<string, SensorInfo*> sensors;
  
  settings["LINEDETECTSETTING"] = _LineDetectSetting;
  settings["LINEDETECTSETTING_SENSOR"] = _SensorLineDetectSetting;  
  settings["DISTANCE"] = distanceCheck;
  settings["TIMER"] = timeCheck;
  settings["CHECK"] = checkSwitch;
  settings["FOLLOWLINE"] = followLine;
  settings["FOLLOWLINE_WAIT"] = followLineWait;
  settings["NAVIGATESETTING"] = navigateCommand;
  settings["GYRO"] = calibrateGyro;
  settings["LINEDETECTCHECK"] = lineDetected;
  
  commands["DELAY"] = new DelayCommand();
  commands["KEYPRESS"] = new KeyPressCommand();
  commands["SEGWAY"] = new SegwayCommand(_Navigate); 
  commands["FOLLOWLINE"] = followLine;
  commands["FOLLOWLINE_WAIT"] = followLineWait;
  commands["NAVIGATE_UPDATE"] = navigateCommand;
  commands["GYRO"] = calibrateGyro;
  commands["WAIT"] = new WaitCommand(checkSwitch);
  
  sensors["HEAD"] = _CameraSensor;
  
  _CommandScript = new CommandScript(parseCommandLine, commands, settings, sensors);
}

Robot::~Robot() {
}
#include <SensorFactory.h>
#include <ParseCommandLine.h>
#include <ComController.h>
#include <DistanceCheck.h>
#include <PortCheck.h>
#include <Servo.h>
#include <SwitchCheck.h>
#include <LineCheck.h>
#include <DistanceSensorCheck.h>
#include <WaitCommand.h>
#include <FollowLineSetting.h>
#include <FollowLineCommand.h>
#include <DirectComCommand.h>
#include <MoveFixedDirCommand.h>
#include <SpeedCommand.h>
#include <AddDistanceCommand.h>
#include <ResetMoveCommand.h>
#include <SnapshotCommand.h>
#include <StartDistanceCommand.h>
#include <ServoCommand.h>
#include <LEDCommand.h>
#include <EmptyLog.h>
#include <ConsolLog.h>
#include <FileLogger.h>
#include <LoggingSetting.h>
#include <NavigateToLine.h>
#include <SearchForLine.h>
#include <TurnToCenterLine.h>
#include <NavigateToBall.h>
#include <DetectObject.h>

SensorFactory::SensorFactory(Logging* logger, map<string, int> commands) {
  ComPort* comPort = new ComPort();
  
  EmptyLog* emptyLog = new EmptyLog();
  Logging* fileLog = new FileLogger("ScriptLog.txt");
  
  LoggingSetting* loggingSetting = new LoggingSetting(emptyLog, logger, fileLog);
  
  cv::Rect topRoi(0, 40, 320, 2);
  LineDetectSetting* topLineDetectSetting = new LineDetectSetting(topRoi, 10, 300, LineDetectSetting::CENTER, LineDetectSetting::VERTICAL, false);
  LineDetect* topLineDetect = new LineDetect(topLineDetectSetting, loggingSetting->GetLogging());

  cv::Rect bottomRoi(0, 200, 320, 2);
  LineDetectSetting* bottomLineDetectSetting = new LineDetectSetting(bottomRoi, 10, 300, LineDetectSetting::CENTER, LineDetectSetting::VERTICAL, false);
  LineDetect* bottomLineDetect = new LineDetect(bottomLineDetectSetting, loggingSetting->GetLogging());

  cv::Rect leftRoi(20, 0, 2, 240);
  LineDetectSetting* leftLineDetectSetting = new LineDetectSetting(leftRoi, 10, 300, LineDetectSetting::CENTER, LineDetectSetting::HORIZONTAL, false);
  LineDetect* leftLineDetect = new LineDetect(leftLineDetectSetting, loggingSetting->GetLogging());

  cv::Rect rightRoi(300, 0, 2, 240);
  LineDetectSetting* rightLineDetectSetting = new LineDetectSetting(rightRoi, 10, 300, LineDetectSetting::CENTER, LineDetectSetting::HORIZONTAL, false);
  LineDetect* rightLineDetect = new LineDetect(rightLineDetectSetting, loggingSetting->GetLogging());

  ComController* comController = new ComController(comPort, commands);

  DistanceCheck* distanceCheck = new DistanceCheck(comController, 1000);

  DistanceSensorCheck* distanceSensorCheck = new DistanceSensorCheck(comController);

  PortCheck* portCheck = new PortCheck(comController, 2);

  Servo* Servo0 = new Servo(comController, 0);
  Servo* Servo1 = new Servo(comController, 1);
  
  CameraDetector* cameraDetector = new CameraDetector();

  LineCheck* leftLineCheck = new LineCheck(leftLineDetect, cameraDetector, 1, true);

  LineCheck* rightLineCheck = new LineCheck(rightLineDetect, cameraDetector, 1, true);

  LineCheck* topLineCheck = new LineCheck(topLineDetect, cameraDetector, 1, false);

  LineCheck* bottomLineCheck = new LineCheck(bottomLineDetect, cameraDetector, 1, false);

  SwitchCheck* switchCheck = new SwitchCheck(comController, portCheck, distanceCheck, leftLineCheck, bottomLineCheck, distanceSensorCheck);

  FollowLineSetting* followLineSetting = new FollowLineSetting(12, 100, 20, 10);

  ParseCommandLine* parseCommandLine = new ParseCommandLine(commands);
  
  SnapshotCommand* snapshotCommand = new SnapshotCommand(cameraDetector, bottomLineDetectSetting, topLineDetectSetting, leftLineDetectSetting, rightLineDetectSetting);
  
  FindLineSetting* findLineSetting = new FindLineSetting(leftLineDetect, rightLineDetect, topLineDetect);
  SearchForLine* searchForLine = new SearchForLine(findLineSetting, comController, cameraDetector);
  NavigateToLine* navigateToLine = new NavigateToLine(findLineSetting, comController, cameraDetector);
  TurnToCenterLine* turnToLine = new TurnToCenterLine(cameraDetector, comController, bottomLineDetect);
  
  DetectObject* detectObject = new DetectObject();
  NavigateToBall* navigateToBall = new NavigateToBall(cameraDetector, detectObject, comController);
  
  _sensors["DISTANCE"] = distanceCheck;
  _sensors["TOPLINE"] = topLineCheck;
  _sensors["BOTTOMLINE"] = bottomLineCheck;
  _sensors["LEFTLINE"] = leftLineCheck;
  _sensors["RIGHTLINE"] = rightLineCheck;
  _sensors["SERVO0"] = Servo0;
  _sensors["SERVO1"] = Servo1;
  
  _commands["DELAY"] = new DelayCommand();
  _commands["WAIT"] = new WaitCommand(switchCheck);
  _commands["SENDDATA"] = new DirectComCommand(comController);
  _commands["SNAPSHOT"] = snapshotCommand;
  _commands["LINE"] = new FollowLineCommand(cameraDetector, comController, followLineSetting, switchCheck, bottomLineDetect, topLineDetect);
  _commands["KEYPRESS"] = new KeyPressCommand();
  _commands["SPEEDDIRECTION"] = new MoveFixedDirCommand(comController, switchCheck);
  _commands["SETSPEEDDIR"] = new SpeedCommand(comController);
  _commands["SETDISTANCE"] = new AddDistanceCommand(comController);
  _commands["RESETMOVEMENT"] = new ResetMoveCommand(comController);
  _commands["STARTDISTANCE"] = new StartDistanceCommand(comController);
  _commands["SEARCHFORLINE"] = searchForLine;
  _commands["NAVIGATETOLINE"] = navigateToLine;
  _commands["TURNTOLINE"] = turnToLine;
  _commands["NAVIGATETOBALL"] = navigateToBall;
  _commands["SERVO"] = new ServoCommand(comController);
  _commands["LED"] = new LEDCommand(comController);

  _settings["SNAPSHOT"] = snapshotCommand;
  _settings["LOGGING"] = loggingSetting;
  _settings["TOPLINEDETECT"] = topLineDetectSetting;
  _settings["BOTTOMLINEDETECT"] = bottomLineDetectSetting;
  _settings["LEFTLINEDETECT"] = leftLineDetectSetting;
  _settings["RIGHTLINEDETECT"] = rightLineDetectSetting;
  _settings["FOLLOWLINE"] = followLineSetting;
  _settings["CHECK"] = switchCheck;
  _settings["BOTTOMLINECHECK"] = bottomLineCheck;
  _settings["LEFTLINECHECK"] = leftLineCheck;
  _settings["DISTANCESENSOR"] = distanceSensorCheck;
  _settings["DISTANCE"] = distanceCheck;
  _settings["PORT"] = portCheck;
  _settings["SEARCHFORLINE"] = searchForLine;
  _settings["NAVIGATETOLINE"] = navigateToLine;
  _settings["TURNTOLINE"] = turnToLine;
  _settings["NAVIGATETOBALL"] = navigateToBall;
}

map<string, Command*> SensorFactory::GetCommands() {
  return this->_commands;
}

map<string, Setting*> SensorFactory::GetSettings() {
  return this->_settings;
}
map<string, SensorInfo*> SensorFactory::GetSensors() {
  return this->_sensors;
}
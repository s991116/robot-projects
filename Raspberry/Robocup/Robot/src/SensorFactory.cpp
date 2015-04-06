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
#include <FollowLineDistance.h>
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
#include <NavigateToBook.h>
#include <TurnToBook.h>
#include <DetectObject.h>
#include <DetectColoredObject.h>
#include <ObjectDetect.h>
#include <MoveDistance.h>

SensorFactory::SensorFactory(map<string, int> commands, string path) {
  ComPort* comPort = new ComPort();

  EmptyLog* emptyLog = new EmptyLog();
  Logging* fileLog = new FileLogger("ScriptLog.txt");
  Logging* logger = new ConsolLog();

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

  ComController* comController = new ComController(comPort, commands, loggingSetting->GetLogging());

  DistanceCheck* distanceCheck = new DistanceCheck(comController, 1000);

  PortCheck* portCheck = new PortCheck(comController, 2);

  Servo* Servo0 = new Servo(comController, 0);
  Servo* Servo1 = new Servo(comController, 1);

  PiCamera* piCamera = new PiCamera();
  CameraNavigation* cameraNavigation = new CameraNavigation(comController);
  RobotCamera* robotCamera = new RobotCamera(piCamera, cameraNavigation);

  DistanceSensorCheck* distanceSensorCheck = new DistanceSensorCheck(comController, cameraNavigation, loggingSetting->GetLogging());

  LineCheck* leftLineCheck   = new LineCheck(leftLineDetect,   robotCamera, 1, true);
  LineCheck* rightLineCheck  = new LineCheck(rightLineDetect,  robotCamera, 1, true);
  LineCheck* topLineCheck    = new LineCheck(topLineDetect,    robotCamera, 1, false);
  LineCheck* bottomLineCheck = new LineCheck(bottomLineDetect, robotCamera, 1, false);

  SwitchCheck* switchCheck = new SwitchCheck(comController, portCheck, distanceCheck, leftLineCheck, rightLineCheck, bottomLineCheck, topLineCheck, distanceSensorCheck);

  FollowLineSetting* followLineSetting = new FollowLineSetting(12, 100, 20, 10);

  SnapshotCommand* snapshotCommand = new SnapshotCommand(robotCamera, bottomLineDetectSetting, topLineDetectSetting, leftLineDetectSetting, rightLineDetectSetting);

  FindLineSetting* findLineSetting = new FindLineSetting(leftLineDetect, rightLineDetect, topLineDetect);
  SearchForLine* searchForLine = new SearchForLine(findLineSetting, comController, robotCamera);
  NavigateToLine* navigateToLine = new NavigateToLine(findLineSetting, comController, robotCamera);
  TurnToCenterLine* turnToLine = new TurnToCenterLine(robotCamera, comController, bottomLineDetect);

  DetectObject* detectObject = new DetectColoredObject();
  NavigateToBall* navigateToBall = new NavigateToBall(robotCamera, detectObject, comController);
  FollowLineDistance* followLineDistance = new FollowLineDistance(robotCamera, comController, followLineSetting, distanceCheck, bottomLineDetect, topLineDetect);
  
  float minDetectPosition = 0.9;
  std::string templateBook1 = path + "TemplateBook_1.jpg";
  std::string templateBook2 = path + "TemplateBook_2.jpg";

  ObjectDetect* detectBook1 = new ObjectDetect(templateBook1, minDetectPosition, loggingSetting->GetLogging());
  ObjectDetect* detectBook2 = new ObjectDetect(templateBook2, minDetectPosition, loggingSetting->GetLogging());

  StartDistanceCommand* startDistanceCommand = new StartDistanceCommand(comController);
  AddDistanceCommand* addDistanceCommand = new AddDistanceCommand(comController);
  MoveDistance* moveDistance = new MoveDistance(addDistanceCommand, startDistanceCommand);
  
  NavigateToBook* navigateToBook = new NavigateToBook(robotCamera, followLineDistance, moveDistance, detectBook1, detectBook2, loggingSetting->GetLogging());
  TurnToBook* turnToBook = new TurnToBook(robotCamera, moveDistance, detectBook1, detectBook2, loggingSetting->GetLogging());
    
  _sensors["DISTANCE"] = distanceCheck;
  _sensors["TOPLINE"] = topLineCheck;
  _sensors["BOTTOMLINE"] = bottomLineCheck;
  _sensors["LEFTLINE"] = leftLineCheck;
  _sensors["RIGHTLINE"] = rightLineCheck;
  _sensors["SERVO0"] = Servo0;
  _sensors["SERVO1"] = Servo1;
  _sensors["DISTANCESENSOR"] = distanceSensorCheck;
  _sensors["PORT"] = portCheck;
  
  _commands["DELAY"] = new DelayCommand();
  _commands["WAIT"] = new WaitCommand(switchCheck);
  _commands["SENDDATA"] = new DirectComCommand(comController);
  _commands["SNAPSHOT"] = snapshotCommand;
  _commands["LINE"] = new FollowLineCommand(robotCamera, comController, followLineSetting, switchCheck, bottomLineDetect, topLineDetect);
  _commands["LINEDISTANCE"] = followLineDistance; 
  _commands["KEYPRESS"] = new KeyPressCommand();
  _commands["SPEEDDIRECTION"] = new MoveFixedDirCommand(comController, switchCheck);
  _commands["SETSPEEDDIR"] = new SpeedCommand(comController);
  _commands["SETDISTANCE"] = addDistanceCommand;
  _commands["RESETMOVEMENT"] = new ResetMoveCommand(comController);
  _commands["STARTDISTANCE"] = startDistanceCommand;
  _commands["SEARCHFORLINE"] = searchForLine;
  _commands["NAVIGATETOLINE"] = navigateToLine;
  _commands["TURNTOLINE"] = turnToLine;
  _commands["NAVIGATETOBALL"] = navigateToBall;
  _commands["NAVIGATETOBOOK"] = navigateToBook;
  _commands["TURNTOBOOK"] = turnToBook;
  _commands["SERVO"] = new ServoCommand(comController);
  _commands["LED"] = new LEDCommand(comController);
  _commands["MOVEDISTANCE"] = moveDistance;

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
  _settings["RIGHTLINECHECK"] = rightLineCheck;
  _settings["TOPLINECHECK"] = topLineCheck;
  _settings["DISTANCESENSOR"] = distanceSensorCheck;
  _settings["DISTANCE"] = distanceCheck;
  _settings["PORT"] = portCheck;
  _settings["SEARCHFORLINE"] = searchForLine;
  _settings["NAVIGATETOLINE"] = navigateToLine;
  _settings["TURNTOLINE"] = turnToLine;
  _settings["NAVIGATETOBALL"] = navigateToBall;
  _settings["NAVIGATETOBOOK"] = navigateToBook;
  _settings["TURNTOBOOK"] = turnToBook;
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
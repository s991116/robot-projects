#include <MoveCommand.h>
#include <View.h>
#include <Controller.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <SpeedControl.h>
#include <ConsolePrint.h>

Controller::Controller(View* view, CommandScript* commandScript, map<string, Command*> commands, map<string, SensorInfo*> sensorInfo) {
  this->view = view;
  this->view->AddListener(this);
  this->_commandScript = commandScript;
  this->_commands = commands;
  this->_sensorInfo = sensorInfo;
  Stop();
  this->Servo0Position = 90;
  this->Servo1Position = 90;
  this->Servo0MinPosition = 0;
  this->Servo0MaxPosition = 180;
  this->Servo1MinPosition = 0;
  this->Servo1MaxPosition = 180;
}

void Controller::Start() {
  this->view->InitializeView();
  QuitProgram = false;
  while (!QuitProgram) {
    this->view->UpdateView();
    view->GetCommand();
  }
}

void Controller::SetMoveCommand(MoveCommand moveCommand) {
  this->_moveCommand = moveCommand;
  Command* speedCmd = this->_commands["SETSPEEDDIR"];
  std::vector<int> data;

  map<MoveCommand, int> dirCommand = SpeedControl::CreateDirCommands();
  map<MoveCommand, int> rotationCommand = SpeedControl::CreateRotationCommands();
  map<MoveCommand, int> speedCommand = SpeedControl::CreateSpeedCommands();

  int dir = dirCommand[moveCommand];
  int rotation = rotationCommand[moveCommand];
  int speed = speedCommand[moveCommand];

  data.push_back(dir);
  data.push_back(rotation);
  data.push_back(speed);

  speedCmd->Execute(data);
}

MoveCommand Controller::GetMoveCommand() {
  return _moveCommand;
}

void Controller::RunScript(std::string filename) {
  try {
    this->_commandScript->RunFileScript(filename);
  }
  catch(string error)
  {
    string exception = "Exception: " + error;
    ConsolePrint::PrintError(exception);
  }
  Stop();
}

void Controller::Stop() {
  Command* speedCmd = this->_commands["SETSPEEDDIR"];
  std::vector<int> data;

  data.push_back(0);
  data.push_back(0);
  data.push_back(0);

  speedCmd->Execute(data);
}

void Controller::SavePicture() {
  Command* speedCmd = this->_commands["SNAPSHOT"];
  std::vector<int> data;
  speedCmd->Execute(data);
}

void Controller::StepServoUp() {
    this->Servo0Position++;
    this->SetServo(0, this->Servo0Position, this->Servo0MinPosition, this->Servo0MaxPosition); 
}

void Controller::StepServoDown() {
    this->Servo0Position--;
    this->SetServo(0, this->Servo0Position, this->Servo0MinPosition, this->Servo0MaxPosition); 
}

void Controller::StepServoLeft() {
    this->Servo1Position++;
    this->SetServo(1, this->Servo1Position, this->Servo1MinPosition, this->Servo1MaxPosition); 
}

void Controller::StepServoRight() {
    this->Servo1Position--;
    this->SetServo(1, this->Servo1Position, this->Servo1MinPosition, this->Servo1MaxPosition); 
}

std::string Controller::GetServoLeftRightPosition() {
    SensorInfo* servo = this->_sensorInfo["SERVO1"];
	return servo->GetStatus();
}

std::string Controller::GetServoUpDownPosition() {
    SensorInfo* servo = this->_sensorInfo["SERVO0"];
	return servo->GetStatus();
}

void Controller::SetServo(int servoIndex, int position, int minPosition, int maxPosition)
{
  Command* servoCmd = this->_commands["SERVO"];
  std::vector<int> data;
  data.push_back(servoIndex);
  data.push_back(position);
  data.push_back(minPosition);
  data.push_back(maxPosition);
  servoCmd->Execute(data);
}

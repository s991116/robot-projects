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

Controller::Controller(View* view, CommandScript* commandScript, map<string, Command*> commands) {
  this->view = view;
  this->view->AddListener(this);
  this->_commandScript = commandScript;
  this->_commands = commands;
  Stop();
  this->Servo0Position = 90;
  this->Servo1Position = 90;
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
    Command* servoCmd = this->_commands["SERVO"];
    std::vector<int> data;
    this->Servo0Position++;
    data.push_back(0);  
    data.push_back(this->Servo0Position);		
	servoCmd->Execute(data);
}

void Controller::StepServoDown() {
    Command* servoCmd = this->_commands["SERVO"];
    std::vector<int> data;
    this->Servo0Position--;
    data.push_back(0);  
    data.push_back(this->Servo0Position);	
	servoCmd->Execute(data);
}

void Controller::StepServoLeft() {
    Command* servoCmd = this->_commands["SERVO"];
    std::vector<int> data;
    this->Servo1Position++;
    data.push_back(1);  
    data.push_back(this->Servo1Position);
	servoCmd->Execute(data);
}

void Controller::StepServoRight() {
    Command* servoCmd = this->_commands["SERVO"];
    std::vector<int> data;
    this->Servo1Position--;
    data.push_back(1);  
    data.push_back(this->Servo1Position);		
	servoCmd->Execute(data);
}
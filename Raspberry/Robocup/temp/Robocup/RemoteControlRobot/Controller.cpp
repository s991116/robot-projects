#include "Common.h"
#include "View.h"
#include "Controller.h"
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include "SpeedControl.h"
#include "ConsolePrint.h"

Controller::Controller(View* view, CommandScript* commandScript, map<string, Command*> commands) {
  this->view = view;
  this->view->AddListener(this);
  this->_commandScript = commandScript;
  this->_commands = commands;
  Stop();
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
//  this->cameraDetector->SavePicture("TestPicture.jpg");
}
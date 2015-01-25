#include <MoveCommand.h>
#include <View.h>
#include <Controller.h>
#include <KeyCodes.h>
#include <stdio.h>
#include <BufferedInput.h>
#include <iostream>
#include <sstream>

void View::AddListener(Controller* controller) {
  _controller = controller;
  _currentScript = "TestScript.txt";
}

void View::InitializeView() {
  this->PrintHelp();
}

void View::PrintHelp() {
  cout << "Robot Manual Move program started." << std::endl;
  cout << "Quit: ESC / 'X" << std::endl;
  cout << "Move: 'Q','W','E','A','S','D'" << std::endl;
  cout << "RunScript: 'R'" << std::endl;
  cout << "Save picture: 'B'" << std::endl;
}

void View::GetMoveCommand(int keyCode) {
  switch (keyCode) {
    case KEYCODE_w:
      this->_controller->SetMoveCommand(MoveForward);
      return;

    case KEYCODE_q:
      this->_controller->SetMoveCommand(MoveLeft);
      return;

    case KEYCODE_a:
      this->_controller->SetMoveCommand(TurnLeft);
      return;

    case KEYCODE_e:
      this->_controller->SetMoveCommand(MoveRight);
      return;

    case KEYCODE_d:
      this->_controller->SetMoveCommand(TurnRight);
      return;

    case KEYCODE_s:
      this->_controller->SetMoveCommand(MoveBack);
      return;

    default:
      this->_controller->SetMoveCommand(Stop);
      return;
  }
}

void View::GetCommand() {
  BufferedInput bufInput;
  bufInput.off();
  int keyCode = getchar();  
  bufInput.on();
  this->GetMoveCommand(keyCode);
  switch (keyCode) {
    case KEYCODE_r:
     _controller->RunScript(GetScript());
      break;

    case KEYCODE_ESC:
    case KEYCODE_x:
      this->_controller->QuitProgram = true;
      break;

    case KEYCODE_b:
      this->_controller->SavePicture();
      break;
  }
}

void View::UpdateView() {

  MoveCommand command;
  command = this->_controller->GetMoveCommand();

  switch (command) {
    case Stop:
      std::cout << "Stopped" << std::endl; //printw("Stopped\n");
      break;
    case MoveForward:
      std::cout << "Forward" << std::endl; //printw("Move Forward\n");
      break;
    case MoveBack:
      std::cout << "Back" << std::endl; //printw("Move Back\n");
      break;
    case MoveLeft:
      std::cout << "Left" << std::endl; //printw("Move Left\n");
      break;
    case MoveRight:
      std::cout << "Right" << std::endl; //printw("Move Right\n");
      break;
    case TurnLeft:
      std::cout << "Turn left" << std::endl; //printw("Turn left\n");
      break;
    case TurnRight:
      std::cout << "Turn right" << std::endl; //printw("Turn Right\n");
      break;
  }
}

string View::GetScript() {
  std::cout << "Enter to run last script ('" << this->_currentScript << "')." << std::endl;
  std::cout << "Scriptname: ";
  std::string scriptName = "";
  std::getline(cin,scriptName);
  if(!scriptName.empty())
    this->_currentScript = scriptName;
  
  return this->_currentScript;
}
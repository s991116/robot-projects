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
  cout << "Sensor info: 'I'" << std::endl;
  cout << "Servo: 'U','J','H','K'" << std::endl;
  cout << "RunScript: 'R'" << std::endl;
  cout << "Save picture: 'V'(Line), 'B'(Ball), 'N'(Book right), 'M'(Book front)" << std::endl;
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

    case KEYCODE_v:
      this->_controller->SavePicture(0);
	  std::cout << "Distance:  " <<  this->_controller->GetSensorInfo("DISTANCESENSOR") << std::endl;
      break;

	case KEYCODE_n:
      this->_controller->SavePicture(1);
	  std::cout << "Distance:  " <<  this->_controller->GetSensorInfo("DISTANCESENSOR") << std::endl;
      break;

	case KEYCODE_m:
      this->_controller->SavePicture(4);
	  std::cout << "Distance:  " <<  this->_controller->GetSensorInfo("DISTANCESENSOR") << std::endl;
      break;

	  case KEYCODE_b:
      this->_controller->SavePicture(2);
	  std::cout << "Distance:  " <<  this->_controller->GetSensorInfo("DISTANCESENSOR") << std::endl;
      break;
  
    case KEYCODE_h:
      this->_controller->StepServoLeft();
      std::cout << "Servo Left. " <<  this->_controller->GetSensorInfo("SERVO1") << std::endl;
      return;

    case KEYCODE_k:
      this->_controller->StepServoRight();
      std::cout << "Servo Right. " <<  this->_controller->GetSensorInfo("SERVO1") << std::endl;
	  return;

	case KEYCODE_u:
	  this->_controller->StepServoUp();
      std::cout << "Servo Up. " <<  this->_controller->GetSensorInfo("SERVO0") << std::endl;
	  return;

	case KEYCODE_j:
	  this->_controller->StepServoDown();
	  std::cout << "Servo Down. " <<  this->_controller->GetSensorInfo("SERVO0") << std::endl;
	  return;

	case KEYCODE_i:
	  std::cout << "Average distance:  " <<  this->_controller->GetSensorInfo("DISTANCE") << std::endl;
	  std::cout << "Top line:  " <<  this->_controller->GetSensorInfo("TOPLINE") << std::endl;
	  std::cout << "Bottom line:  " <<  this->_controller->GetSensorInfo("BOTTOMLINE") << std::endl;
	  std::cout << "Left side:  " <<  this->_controller->GetSensorInfo("LEFTLINE") << std::endl;
	  std::cout << "Right side:  " <<  this->_controller->GetSensorInfo("RIGHTLINE") << std::endl;
	  return;
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

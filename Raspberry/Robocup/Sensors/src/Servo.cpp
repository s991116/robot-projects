#include <Servo.h>
#include <Convert.h>

Servo::Servo(ComController* comController, int servoNr) {
  this->_ComController = comController;
  this->servoNr = servoNr;
}

std::string Servo::GetStatus()
{
	int position = this->_ComController->GetServoPosition(this->servoNr);
	return "Servo-" + Convert::IntToString(this->servoNr) + " Position: " + Convert::IntToString(position);
}
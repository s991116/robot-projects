#include <iostream>
#include <ComController.h>
#include <ComMessage.h>
#define RESPONSELENGTH
#include <MotorControllerCmd.h>

ComController::ComController(ComPort* comPort, map<string, int> commands) {
  m_ComPort = comPort;
  m_Commands = commands;
}

int ComController::SendCommand(int command, short data) {
  SendMessage((char) command, data);
  return GetMessage((char) command);
}

void ComController::SendMessage(char command, short data) {

  char* message = new char[3];
  this->CleanReceivedData();

  ComMessage::GenerateMessage(command, data, message);

  m_ComPort->Send(message);
  delete message;
}

int ComController::GetMessage(char command) {
  const int MaxRetryCount = 50000;
  char responseLength = ResponseLength[(int)command];
  int receivedData = 0;
  if (responseLength != 0) {
    char bitShift[4] = {24, 16, 8, 0};
    for (char i = 0; i < responseLength; i++) {
      unsigned char receivebuffer[1];

      char result;
      int retry = 0;
      do {
        result = m_ComPort->ReceiveChar(receivebuffer);
        retry++;
      } while (result != 1 && retry < MaxRetryCount);

      if (retry >= MaxRetryCount)
        std::cout << "ERROR: No data received. " << " , Retry(" << retry << ")" << std::endl;

      receivedData |= int(receivebuffer[0] << bitShift[(int)i]);
    }
  }
  return receivedData;
}

void ComController::CleanReceivedData() {
  unsigned char receivebuffer[1];
  int retry = 0;
  char result;
  do {
    result = m_ComPort->ReceiveChar(receivebuffer);
    retry++;
  } while (result == 1 && retry < 10000);
  if (retry > 10000)
    std::cout << "ERROR: No data received from comport." << std::endl;
}

void ComController::ResetMoveCommand() {
  this->SendCommand(m_Commands["SET_SPEED"], 0);
}

int ComController::GetMoveDistance() {
  return this->SendCommand(m_Commands["GET_MOVE_BY_DISTANCE"], 0);
}

void ComController::SetDirection(Direction* direction) {
  this->_Direction = direction;
  this->SendCommand(m_Commands["SET_DIRECTION"], direction->GetDirection());
  this->SendCommand(m_Commands["SET_ROTATION"], direction->GetRotation());
  this->SendCommand(m_Commands["SET_SPEED"], direction->GetSpeed());
}

Direction* ComController::GetDirection() {
  return _Direction;
}

void ComController::AddDistanceCommand(Direction* direction, int distance) {
  
  this->SendCommand(m_Commands["ADD_MOVE_BY_DISTANCE"], 1);
  this->SetDirection(direction);
  this->SendCommand(m_Commands["SET_DISTANCE"], distance);
  this->SendCommand(m_Commands["ADD_MOVE_BY_DISTANCE"], 0);
}

void ComController::StartDistanceCommand() {
  this->SendCommand(m_Commands["SET_MOVE_BY_DISTANCE"], 1);
}

int ComController::DistanceCommandRunning() {
  return this->SendCommand(m_Commands["GET_MOVE_BY_DISTANCE"], 0);
}

int ComController::GetAverageDistanceCommand() {
  int distA = this->SendCommand(m_Commands["GET_MOTOR_A_DISTANCE"], 0);
  int distB = this->SendCommand(m_Commands["GET_MOTOR_B_DISTANCE"], 0);

  return (distA / 2) + (distB / 2);
}

void ComController::ResetDistanceCommand() {
  this->SendCommand(m_Commands["RESET_MOTOR_DISTANCE"], 0);
}

int ComController::GetPortCount() {
  return this->SendCommand(m_Commands["GET_PORT_COUNT"], 0);
}

int ComController::GetDistanceSensor() {
  return this->SendCommand(m_Commands["GET_DISTANCESENSOR"], 0);
}

void ComController::SetServoPosition(int servoNr, int position)
{
	short data = (servoNr << 8) | position;
	this->SendCommand(m_Commands["CMD_SET_SERVO_POSITION"], data);
}

void ComController::SetServoMaxPosition(int servoNr, int position)
{
	short data = (servoNr << 8) | position;
	this->SendCommand(m_Commands["CMD_SET_SERVO_MAX_POSITION"], data);
}

void ComController::SetServoMinPosition(int servoNr, int position)
{
	short data = (servoNr << 8) | position;
	this->SendCommand(m_Commands["CMD_SET_SERVO_MIN_POSITION"], data);
}

int ComController::GetServoPosition(int servoNr) {
  return this->SendCommand(m_Commands["CMD_GET_SERVO_POSITION"], servoNr);
}

void ComController::SetLEDMode(int LEDnr, LEDMode mode) {
	short data = (LEDnr << 8) | (static_cast<int> (mode));
	this->SendCommand(m_Commands["CMD_SET_LED_MODE"], data);
}

ComController::~ComController() {
}

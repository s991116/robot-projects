#include <TurnToBook.h>

TurnToBook::TurnToBook(RobotCamera* robotCamera, ComController* comController, LoggingSetting* loggingSetting) {

  _RobotCamera = robotCamera;
  _ComController = comController;
  _LoggingSetting = loggingSetting;
}

std::string TurnToBook::Execute(std::vector<int> input) {
  _ComController->SetLEDMode(LEDColor::Green, LEDMode::On);
  _ComController->SetLEDMode(LEDColor::Red, LEDMode::Off);

  return "";
}

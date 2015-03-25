#include <TurnToBook.h>

TurnToBook::TurnToBook(RobotCamera* robotCamera, ComController* comController, ObjectDetect* detectBook1, ObjectDetect* detectBook2, Logging* logging) {

  _RobotCamera = robotCamera;
  _ComController = comController;
  _Logging = logging;
  _DetectBook1 = detectBook1;
  _DetectBook2 = detectBook2;
}

std::string TurnToBook::Execute(std::vector<int> input) {
  _ComController->SetLEDMode(LEDColor::Green, LEDMode::On);
  _ComController->SetLEDMode(LEDColor::Red, LEDMode::Off);

  _Logging->Log("Turning towards book...");
  _image = _RobotCamera->GetNextFrame(CameraPosition::NAVIGATE_TO_BOOK);

  return "";
}

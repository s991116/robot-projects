#include <PortCheck.h>
#include <Convert.h>

PortCheck::PortCheck(ComController* comController, int portCount) {
  _ComController = comController;
  _DeltaCount = portCount;
  SettingsInt["COUNT"] = &_DeltaCount;
}

void PortCheck::Prepare() {
  _TargetCount = _DeltaCount + _ComController->GetPortCount();
}

std::string PortCheck::GetStatus() {
  int currentCount = _ComController->GetPortCount();
  return "Port count: " + Convert::IntToString(currentCount);
}


bool PortCheck::Test() {
  int currentCount = _ComController->GetPortCount();
  return (currentCount < _TargetCount);
}
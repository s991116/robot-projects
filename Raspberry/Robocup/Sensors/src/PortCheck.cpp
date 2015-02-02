#include <PortCheck.h>

PortCheck::PortCheck(ComController* comController, int portCount) {
  _ComController = comController;
  _DeltaCount = portCount;
  SettingsInt["COUNT"] = &_DeltaCount;
}

void PortCheck::Prepare() {
  _TargetCount = _DeltaCount + _ComController->GetPortCount();
}

bool PortCheck::Test() {
  int currentCount = _ComController->GetPortCount();
  return (currentCount < _TargetCount);
}
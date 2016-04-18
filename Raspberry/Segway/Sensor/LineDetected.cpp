#include "LineDetected.h"

LineDetected::LineDetected(CameraSensor* cameraSensor) {
    _CameraSensor = cameraSensor;
    _NoLineDetected = true;
    this->SettingsBool["WAIT_TO_NO_LINE_DETECTED"] = &_NoLineDetected;
}

void LineDetected::Prepare() {
    
}

bool LineDetected::Test() {
    LineInfo* lineInfo = _CameraSensor->GetSensorLine();
    return(lineInfo->LineDetected() != _NoLineDetected);
}

LineDetected::~LineDetected() {
}
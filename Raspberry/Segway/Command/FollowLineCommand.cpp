#include "FollowLineCommand.h"
#include <cmath>

FollowLineCommand::FollowLineCommand(Check* check, CameraSensor* cameraSensor, Navigate* navigate, Logging* logging) {
    _Check = check;
    _CameraSensor = cameraSensor;
    _Navigate = navigate;
    _Logging = logging;
    SettingsFloat["SIDECORRECTION"] = &_SideCorrectionFactor;
    SettingsFloat["SPEEDCORRECTION"] = &_SpeedCorrectionFactor;
    SettingsFloat["MAXSPEED"] = &_MaxSpeed;
}

std::string FollowLineCommand::Execute(vector<int> input) {
    _Check->Prepare();
    _Logging->Log("Sidecorrection", _SideCorrectionFactor);
    while(!_Check->Test()) {
        LineInfo* lineInfo = _CameraSensor->GetLine();
        _Logging->Log("CameraSensor called");
        if(lineInfo->LineDetected())
        {
            float linePosition = lineInfo->GetNormalizePosition();
            _Logging->Log("Lineposition", linePosition);
            double sideCorrection = lineInfo->GetNormalizePosition() * _SideCorrectionFactor;
            _Navigate->TurnSpeed(sideCorrection);            
            double speedCorrection = _MaxSpeed - std::abs(lineInfo->GetNormalizePosition()) * _SpeedCorrectionFactor;
            _Navigate->ForwardSpeed(speedCorrection);
        }
        else
        {
            _Logging->Log("No line found");
            _Navigate->ForwardSpeed(0);
        }
        
    }
    return "Following Line ended";
}

FollowLineCommand::~FollowLineCommand() {
}
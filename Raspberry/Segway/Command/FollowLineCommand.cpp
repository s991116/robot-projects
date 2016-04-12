#include "FollowLineCommand.h"

FollowLineCommand::FollowLineCommand(Check* check, CameraSensor* cameraSensor, Navigate* navigate, Logging* logging) {
    _Check = check;
    _CameraSensor = cameraSensor;
    _Navigate = navigate;
    _Logging = logging;
    SettingsFloat["SIDECORRECTION"] = &_SideCorrectionFactor;
}

std::string FollowLineCommand::Execute(vector<int> input) {
    _Check->Prepare();
    _Logging->Log("Sidecorrection", _SideCorrectionFactor);
    while(!_Check->Test()) {
        _Logging->Log("Test");
        LineInfo* lineInfo = _CameraSensor->GetLine();
        _Logging->Log("CameraSensor called");
        if(lineInfo->LineDetected())
        {
            float linePosition = lineInfo->GetNormalizePosition();
            _Logging->Log("Lineposition", linePosition);
            double sideCorrection = lineInfo->GetNormalizePosition() * _SideCorrectionFactor;
            _Navigate->TurnSpeed(sideCorrection);
        }
        else
            _Logging->Log("No line found");
        
    }
    return "Following Line ended";
}

FollowLineCommand::~FollowLineCommand() {
}
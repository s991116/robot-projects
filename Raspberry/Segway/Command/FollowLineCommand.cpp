#include "FollowLineCommand.h"

FollowLineCommand::FollowLineCommand(Check* check, CameraSensor* cameraSensor, Navigate* navigate) {
    _Check = check;
    _CameraSensor = cameraSensor;
    _Navigate = navigate;
    SettingsFloat["SIDECORRECTION"] = &_SideCorrectionFactor;
}

std::string FollowLineCommand::Execute(vector<int> input) {
    _Check->Prepare();
    
    while(!_Check->Test()) {
        LineInfo* lineInfo = _CameraSensor->GetLine();
        if(lineInfo->LineDetected())
        {
            double sideCorrection = lineInfo->GetNormalizePosition() * _SideCorrectionFactor;
            _Navigate->TurnSpeed(sideCorrection);
        }
        
    }
    return "Following Line ended";
}

FollowLineCommand::~FollowLineCommand() {
}
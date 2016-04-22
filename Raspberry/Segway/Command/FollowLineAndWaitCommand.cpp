#include "FollowLineAndWaitCommand.h"

FollowLineAndWaitCommand::FollowLineAndWaitCommand(Check* check, CameraSensor* cameraSensor, Navigate* navigate, Logging* logging) {
    _Check = check;
    _CameraSensor = cameraSensor;
    _Navigate = navigate;
    SettingsFloat["SIDECORRECTION"] = &_SideCorrectionFactor;
    SettingsFloat["SPEEDCORRECTION"] = &_SpeedCorrectionFactor;
    SettingsFloat["MAXSPEED"] = &_MaxSpeed;
    _Logging = logging;
}

std::string FollowLineAndWaitCommand::Execute(vector<int> input) {
    _Logging->Log("Start follow line and wait.");
    _Check->Prepare();
    _Logging->Log("Check prepard");
    while (!_Check->Test()) {
        double sideCorrection = 0;
        double speedCorrection = _MaxSpeed;
        LineInfo* lineInfo = _CameraSensor->GetLine();
        _Logging->Log("Line info.");
        LineInfo* sensorLineInfo = _CameraSensor->GetSensorLine();
        _Logging->Log("Sensor Line info.");
        if (!sensorLineInfo->LineDetected()) {
            _Logging->Log("No Sensor line detected");
            float linePosition = lineInfo->GetNormalizePosition();
            sideCorrection = lineInfo->GetNormalizePosition() * _SideCorrectionFactor;
            //sideCorrection = 0;
            speedCorrection = 0;
            _Navigate->TurnSpeed(sideCorrection);
            _Navigate->ForwardSpeed(speedCorrection);
        } else {
            _Logging->Log("Sensor line detected");
            if (lineInfo->LineDetected()) {
                _Logging->Log("Main line detected");
                float linePosition = lineInfo->GetNormalizePosition();
                sideCorrection = lineInfo->GetNormalizePosition() * _SideCorrectionFactor;
                speedCorrection = _MaxSpeed - std::abs(lineInfo->GetNormalizePosition()) * _SpeedCorrectionFactor;
            }
            else
            {
                _Logging->Log("No Main line detected");
            }
            _Navigate->TurnSpeed(sideCorrection);
            _Navigate->ForwardSpeed(speedCorrection);
        }
    }

    return "Follow and wait command ended.";
}

FollowLineAndWaitCommand::~FollowLineAndWaitCommand() {
}


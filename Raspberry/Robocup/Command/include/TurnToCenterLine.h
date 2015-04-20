#ifndef TURNTOCENTERLINE_H
#define	TURNTOCENTERLINE_H

#include <LinePosition.h>
#include <Direction.h>
#include <RobotCamera.h>
#include <ComController.h>
#include <Command.h>
#include <Setting.h>
#include <LineDetect.h>

class TurnToCenterLine : public Command , public Setting {
public:
    TurnToCenterLine(RobotCamera* robotCamera, ComController* comController, LineDetect* bottomLineDetect, LineDetect* topLineDetect);
    std::string Execute(std::vector<int> input);

private:
    bool LineNotInCenter(LineInfo* lineInfo);
    void TurnRobot(LineInfo* lineInfo, ComController* comController);
    CameraMode GetCameraMode();

    RobotCamera* _RobotCamera;
    ComController* _ComController;
	LineDetect* _TopLineDetect;
    LineDetect* _BottomLineDetect;
    Direction* _Direction;
    int _DirectionTurn;
    int _DirectionTurnSpeed;
    float _LineDetectThresshold;
    int _DirectionTurnFactor;
    int _CameraMode;
	bool _BottomLineEnabled;

};

#endif	/* TURNTOCENTERLINE_H */


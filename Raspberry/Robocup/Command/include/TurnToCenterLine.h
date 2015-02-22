#ifndef TURNTOCENTERLINE_H
#define	TURNTOCENTERLINE_H

#include <LinePosition.h>
#include <Direction.h>
#include <PiCamera.h>
#include <ComController.h>
#include <Command.h>
#include <Setting.h>
#include <LineDetect.h>

class TurnToCenterLine : public Command , public Setting {
public:
    TurnToCenterLine(PiCamera* piCamera, ComController* comController, LineDetect* bottomLineDetect);
    std::string Execute(std::vector<int> input);

private:
    bool LineNotInCenter(LineInfo* lineInfo);
    void TurnRobot(LineInfo* lineInfo, ComController* comController);

    PiCamera* _PiCamera;
    ComController* _ComController;
    LineDetect* _BottomLineDetect;
    Direction* _Direction;
    int _DirectionTurn;
    int _DirectionTurnSpeed;
    float _LineDetectThresshold;
    int _DirectionTurnFactor;
};

#endif	/* TURNTOCENTERLINE_H */


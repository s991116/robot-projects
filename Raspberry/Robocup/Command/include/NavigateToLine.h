#ifndef NAVIGATETOLINE_H
#define	NAVIGATETOLINE_H

#include <FindLineSetting.h>
#include <LinePosition.h>
#include <Direction.h>
#include <RobotCamera.h>
#include <ComController.h>
#include <Command.h>
#include <Setting.h>

class NavigateToLine : public Command, public Setting{
public:
    NavigateToLine(FindLineSetting* findLineSetting, ComController* comController, RobotCamera* robotCamera);
    
    std::string Execute(std::vector<int> input);
        
private:
    float CalculateCrosAngle(LinePosition* linePosition);
    float CalculateNormDistance(LinePosition* linePosition);
    void GetCrossValues(float* leftSide, float* rightSide, LinePosition* linePosition);
    void SetDirection(Direction* dir, float angle, float distance);
    float GetAngle(float leftSide, float rightSide);
    float GetDistance(float leftSide, float rightSide, float offset);
    bool WithinThresshold(float distance, float angle);
    FindLineSetting* _FindLineSetting;
    LinePosition* _LinePosition;
    ComController* _ComController;
    RobotCamera* _RobotCamera;
    float _DistanceThresshold;
    float _AngleThresshold;
    int _NavigateSpeed;
    int _AngleSpeed;
    float _MaxAngle;
    float _DistanceOffset;
    Direction* _Direction;
};

#endif	/* NAVIGATETOLINE_H */
#ifndef FOLLOWLINESETTING_H
#define	FOLLOWLINESETTING_H
#include <string>
#include <Setting.h>
#include <Direction.h>
#include <LineInfo.h>
#include <RobotCamera.h>

class FollowLineSetting : public Setting {
public: 
    FollowLineSetting(int correctionFactor, float speedFactor, int maxSpeed, int minSpeed);
    Direction* GetDirection(LineInfo* bottomLine, LineInfo* topLine);
    CameraMode GetCameraMode();
	
private:
    float GetPosition(LineInfo* bottomLine, float* lastPosition);

    Direction* _Direction;
    int _CorrectionFactor;
    float _SpeedFactor;
    int _MaxSpeed;
    int _MinSpeed;
	int _CameraMode;
    float _LastBottomPosition;
    float _LastTopPosition;
};

#endif	/* FOLLOWLINESETTING_H */
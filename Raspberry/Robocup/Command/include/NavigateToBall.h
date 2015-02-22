#ifndef NAVIGATETOBALL_H
#define	NAVIGATETOBALL_H

#include <PiCamera.h>
#include <DetectObject.h>
#include <Position.h>
#include <Direction.h>
#include <ComController.h>
#include <Command.h>
#include <Setting.h>

class NavigateToBall : public Command , public Setting {
public:
    NavigateToBall(PiCamera* piCamera, DetectObject* detectObject, ComController* comController);
    std::string Execute(std::vector<int> input);
    
private:
    void SetDirection(Direction* dir, float angle, float distance);
    bool WithinThresshold(float distance, float angle);
    PiCamera* _PiCamera;
    DetectObject* _DetectObject;
    Position* _Position;
    Direction* _Direction;
    ComController* _ComController;
    
    float _DistanceThresshold;
    float _AngleThresshold;
    int _NavigateSpeed;
    int _AngleSpeed;
    float _DistanceOffset;
};

#endif	/* NAVIGATETOBALL_H */


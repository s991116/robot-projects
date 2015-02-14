#ifndef NAVIGATETOBOOK_H
#define	NAVIGATETOBOOK_H

#include <CameraDetector.h>
#include <DetectSurfObject.h>
#include <Position.h>
#include <Direction.h>
#include <ComController.h>
#include <Command.h>
#include <Setting.h>

class NavigateToBook : public Command , public Setting {
public:
    NavigateToBook(CameraDetector* cameraDetector, DetectSurfObject* detectObject, ComController* comController);
    std::string Execute(std::vector<int> input);
    
private:
    void SetNavigation(Position* pos);
    CameraDetector* _CameraDetector;
    DetectSurfObject* _DetectObject;
    Position* _Position;
    Direction* _Direction;
    ComController* _ComController;    
};

#endif	/* NAVIGATETOBOOK_H */


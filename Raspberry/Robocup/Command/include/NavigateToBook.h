#ifndef NAVIGATETOBOOK_H
#define	NAVIGATETOBOOK_H

#include <RobotCamera.h>
#include <DetectSurfObject.h>
#include <Position.h>
#include <Direction.h>
#include <ComController.h>
#include <Command.h>
#include <Setting.h>

class NavigateToBook : public Command , public Setting {
public:
    NavigateToBook(RobotCamera* robotCamera, DetectSurfObject* detectObject, ComController* comController);
    std::string Execute(std::vector<int> input);
    
private:
    void SetNavigation(Position* pos);
    RobotCamera* _RobotCamera;
    DetectSurfObject* _DetectObject;
    Position* _Position;
    Direction* _Direction;
    ComController* _ComController;    
};

#endif	/* NAVIGATETOBOOK_H */


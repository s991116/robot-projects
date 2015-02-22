#ifndef NAVIGATETOBOOK_H
#define	NAVIGATETOBOOK_H

#include <PiCamera.h>
#include <DetectSurfObject.h>
#include <Position.h>
#include <Direction.h>
#include <ComController.h>
#include <Command.h>
#include <Setting.h>

class NavigateToBook : public Command , public Setting {
public:
    NavigateToBook(PiCamera* piCamera, DetectSurfObject* detectObject, ComController* comController);
    std::string Execute(std::vector<int> input);
    
private:
    void SetNavigation(Position* pos);
    PiCamera* _PiCamera;
    DetectSurfObject* _DetectObject;
    Position* _Position;
    Direction* _Direction;
    ComController* _ComController;    
};

#endif	/* NAVIGATETOBOOK_H */


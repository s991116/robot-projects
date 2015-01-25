#ifndef SEARCHFORLINE_H
#define	SEARCHFORLINE_H

#include "FindLineSetting.h"
#include "LinePosition.h"
#include "ComController.h"
#include "CameraDetector.h"
#include "Direction.h"
#include "Command.h"
#include "Setting.h"

class SearchForLine : public Command, public Setting {
public:
    SearchForLine(FindLineSetting* findLineSetting, ComController* comController, CameraDetector* cameraDetector);
    std::string Execute(std::vector<int> input);

private:
    ComController* _ComController;
    CameraDetector* _CameraDetector;
    int _SearchSpeed;    
    FindLineSetting* _FindLineSetting;
    LinePosition* _LinePosition;
    Direction* _Direction;
};

#endif	/* SEARCHFORLINE_H */
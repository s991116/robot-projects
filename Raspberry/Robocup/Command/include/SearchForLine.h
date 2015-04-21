#ifndef SEARCHFORLINE_H
#define	SEARCHFORLINE_H

#include <FindLineSetting.h>
#include <LinePosition.h>
#include <ComController.h>
#include <RobotCamera.h>
#include <Direction.h>
#include <Command.h>
#include <Setting.h>

class SearchForLine : public Command, public Setting {
public:
    SearchForLine(FindLineSetting* findLineSetting, ComController* comController, RobotCamera* robotCamera);
    std::string Execute(std::vector<int> input);

private:
    ComController* _ComController;
    RobotCamera* _RobotCamera;
    int _SearchSpeed;    
    FindLineSetting* _FindLineSetting;
    LinePosition* _LinePosition;
    Direction* _Direction;
	int _SpecialLine;
};

#endif	/* SEARCHFORLINE_H */
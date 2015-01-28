#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include <string>
#include <CommandScript.h>
#include <map>

class View;

class Controller {
public:
    Controller(View* view, CommandScript* commandScript, map<string, Command*> commands);
    void Start(void);
    void SetMoveCommand(MoveCommand);
    MoveCommand GetMoveCommand(void);
    bool QuitProgram;
    void RunScript(std::string filename);
    void SavePicture(void);
	void StepServoDown(void);
	void StepServoUp(void);
	void StepServoLeft(void);	
	void StepServoRight(void);
	
private:
    void Stop();
    View* view;
    MoveCommand _moveCommand;
    CommandScript* _commandScript;
    map<string, Command*> _commands;
	short Servo0Position;
	short Servo1Position;
};

#endif	/* CONTROLLER_H */


#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include <string>
#include <CommandScript.h>
#include <map>

class View;

class Controller {
public:
    Controller(View* view, CommandScript* commandScript, map<string, Command*> commands, map<string, SensorInfo*>);
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
	std::string GetServoLeftRightPosition();
	std::string GetServoUpDownPosition();

private:
    void Stop();
	void SetServo(int servoIndex, int position, int minPosition, int maxPosition);

	View* view;
    MoveCommand _moveCommand;
    CommandScript* _commandScript;
    map<string, Command*> _commands;
	map<string, SensorInfo*> _sensorInfo;
	short Servo0Position;
	short Servo1Position;
	short Servo0MinPosition, Servo0MaxPosition;
	short Servo1MinPosition, Servo1MaxPosition;
};

#endif	/* CONTROLLER_H */


#ifndef CONTROLLER_H
#define	CONTROLLER_H

#include <string>
#include <CommandScript.h>
#include <MoveCommand.h>
#include <map>

class View;

class Controller {
public:
    Controller(View* view, CommandScript* commandScript, map<string, Command*> commands, map<string, SensorInfo*>, map<string, Setting*> settings);
    void Start(void);
    void SetMoveCommand(MoveCommand);
    MoveCommand GetMoveCommand(void);
    bool QuitProgram;
    void RunScript(std::string filename);
    void SavePicture(int mode);
	void StepServoDown(void);
	void StepServoUp(void);
	void StepServoLeft(void);	
	void StepServoRight(void);
    std::string GetSensorInfo(std::string sensorName);

private:
    void Stop();
	void SetServo(int servoIndex, int position);

	View* view;
    MoveCommand _moveCommand;
    CommandScript* _commandScript;
    map<string, Command*> _commands;
	map<string, SensorInfo*> _sensorInfo;
	map<string, Setting*> _settings;
	short Servo0Position;
	short Servo1Position;
};

#endif	/* CONTROLLER_H */


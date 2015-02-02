#ifndef COMCONTROLLER_H
#define	COMCONTROLLER_H

#include <ComPort.h>
#include <Direction.h>
#include <string>
#include <map>
using namespace std;

class ComController {
public:
    ComController(ComPort* comport, map<string, int> commands);
    virtual ~ComController();
    int SendCommand(int command, short data);
    void ResetMoveCommand();
    int GetMoveDistance();
    void SetDirection(Direction* direction);
    Direction* GetDirection();
    void AddDistanceCommand(Direction* direction, int distance);   
    void StartDistanceCommand();
    int DistanceCommandRunning();
    int GetAverageDistanceCommand();
    void ResetDistanceCommand();
    int GetMessage(char command);
    void CleanReceivedData();

    int GetPortCount();
    int GetDistanceSensor();
	
	void SetServoPosition(int servoNr, int position);
	void SetServoMaxPosition(int servoNr, int position);
	void SetServoMinPosition(int servoNr, int position);
    int GetServoPosition(int servoNr);

private:
    ComPort* m_ComPort;
    map<string, int> m_Commands;
    Direction* _Direction;

    void SendMessage(char command, short data);

};

#endif	/* COMCONTROLLER_H */


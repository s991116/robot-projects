#ifndef COMCONTROLLER_H
#define	COMCONTROLLER_H

#include <ComPort.h>
#include <Direction.h>
#include <string>
#include <map>
#include <Logging.h>

using namespace std;

enum class LEDMode { Off = 0, On = 1, Blink = 2};
enum class LEDColor { Green = 0, Red = 1};

class ComController {
public:
    ComController(ComPort* comport, map<string, int> commands, Logging* logging);
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
    int GetLeftDistanceCommand();
    int GetRightDistanceCommand();
    
    void ResetDistanceCommand();
    
    int GetPortCount();
    int GetDistanceSensor();
    
    void SetServoPosition(int servoNr, int position);
    void SetServoMaxPosition(int servoNr, int position);
    void SetServoMinPosition(int servoNr, int position);
    int GetServoPosition(int servoNr);
    void SetLEDMode(LEDColor LEDnr, LEDMode mode);

private:
    ComPort* m_ComPort;
    map<string, int> m_Commands;
    Logging* _Logging;
    Direction* _Direction;
    
    void SendMessage(char command, short data);
    int GetMessage(char command);
    void CleanReceivedData();
};

#endif	/* COMCONTROLLER_H */
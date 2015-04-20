#ifndef SPEEDCONTROL_H
#define	SPEEDCONTROL_H

#include <map>
#include <MoveCommand.h>

#define SPEEDSTRAIGHT (15)
#define SPEEDTURN (10)
#define DIRTURN (100)

struct SpeedControl {

    static map<MoveCommand, int> CreateDirCommands() {
        map<MoveCommand, int> m;
        m[MoveForward] = 0;
        m[MoveLeft] = -DIRTURN;
        m[TurnLeft] = 0;
        m[MoveRight] = DIRTURN;
        m[TurnRight] = 0;
        m[MoveBack] = -SPEEDSTRAIGHT;
        m[Stop] = 0;
        return m;
    }

    static map<MoveCommand, int> CreateRotationCommands() {
        map<MoveCommand, int> m;
        m[MoveForward] = 0;
        m[MoveLeft] = 0;
        m[TurnLeft] = 1;
        m[MoveRight] = 0;
        m[TurnRight] = 1;
        m[MoveBack] = 0;
        m[Stop] = 0;
        return m;
    }
    
    static map<MoveCommand, int> CreateSpeedCommands() {
        map<MoveCommand, int> m;
        m[MoveForward] = SPEEDSTRAIGHT;
        m[MoveLeft] = SPEEDTURN;
        m[TurnLeft] = -SPEEDTURN;
        m[MoveRight] = SPEEDTURN;
        m[TurnRight] = SPEEDTURN;
        m[MoveBack] = -SPEEDSTRAIGHT;
        m[Stop] = 0;
        return m;
    }
};

#endif	/* SPEEDCONTROL_H */
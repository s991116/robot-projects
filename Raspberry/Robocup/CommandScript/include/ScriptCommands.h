#ifndef SCRIPTCOMMANDS_H
#define	SCRIPTCOMMANDS_H
#include <map>
#include <string>
#include "MotorControllerCmd.h"

using namespace std;

struct ScriptCommands {

    static map<string, int> CreateCommands() {
        map<string, int> m;
        m["SET_MOTOR_A_KP"] = CMD_SET_MOTOR_A_KP;
        m["SET_MOTOR_A_KI"] = CMD_SET_MOTOR_A_KI;
        m["SET_MOTOR_A_KD"] = CMD_SET_MOTOR_A_KD;
        m["SET_MOTOR_B_KP"] = CMD_SET_MOTOR_B_KP;
        m["SET_MOTOR_B_KI"] = CMD_SET_MOTOR_B_KI;
        m["SET_MOTOR_B_KD"] = CMD_SET_MOTOR_B_KD;

        m["GET_MOTOR_A_DISTANCE"] = CMD_GET_MOTOR_A_DISTANCE;
        m["GET_MOTOR_B_DISTANCE"] = CMD_GET_MOTOR_B_DISTANCE;
        m["GET_DISTANCESENSOR"] = CMD_GET_DISTANCESENSOR_MEASURE;
        m["GET_MOTOR_A_TICKSPEED"] = CMD_GET_MOTOR_A_TICKSPEED;
        m["GET_MOTOR_B_TICKSPEED"] = CMD_GET_MOTOR_B_TICKSPEED;

        m["CMD_RETURN_NEGATIV_TEST"] = CMD_RETURN_NEGATIV_TEST;
        m["SET_MOVE_DISTANCE_TO_LIST"] = 21;

        m["SET_DIR_KP"] = CMD_SET_DIR_KP;
        m["SET_DIR_KI"] = CMD_SET_DIR_KI;
        m["SET_DIR_KD"] = CMD_SET_DIR_KD;

        m["SET_MOVE_BY_DISTANCE"] = CMD_SET_MOVE_BY_DISTANCE;
        m["GET_MOVE_BY_DISTANCE"] = CMD_GET_MOVE_BY_DISTANCE;
        m["ADD_MOVE_BY_DISTANCE"] = CMD_ADD_MOVE_BY_DISTANCE;
        m["SET_DISTANCE"] = CMD_SET_DISTANCE;
        m["SET_DIRECTION"] = CMD_SET_DIRECTION;
        m["SET_ROTATION"] = CMD_SET_ROTATION;
        m["SET_SPEED"] = CMD_SET_SPEED;
        m["RESET_MOTOR_DISTANCE"] = CMD_RESET_MOTOR_DISTANCE;
        m["GET_PORT_COUNT"] = CMD_GET_PORT_COUNT;
        m["RESET_PORT_COUNT"] = CMD_RESET_PORT_COUNT;
        return m;
    }
};


#endif	/* SCRIPTCOMMANDS_H */


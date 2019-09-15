const CMD_SET_TEST_VALUE       = (0x10)
const CMD_SET_MOVEMENT         = (0x11)
const CMD_SET_SERVO_1_POSITION = (0x12)
const CMD_SET_SERVO_2_POSITION = (0x13)
const CMD_SET_BATTERY_ALARM    = (0x14)
const CMD_SET_PID_P_LEVEL      = (0x15)
const CMD_SET_PID_I_LEVEL      = (0x16)
const CMD_SET_PID_D_LEVEL      = (0x17)
const CMD_SET_DISTANCESENSOR   = (0x18)
const CMD_SET_BALANCE_MODE     = (0x19)
const CMD_SET_LIGHT            = (0x1A)

const CMD_GET_TEST_VALUE       = (0x20)
const CMD_GET_MOVEMENT         = (0x21)
const CMD_GET_SERVO_1_POSITION = (0x22)
const CMD_GET_SERVO_2_POSITION = (0x23)
const CMD_GET_BATTERY_ALARM    = (0x24)
const CMD_GET_PID_P_LEVEL      = (0x25)
const CMD_GET_PID_I_LEVEL      = (0x26)
const CMD_GET_PID_D_LEVEL      = (0x27)
const CMD_GET_DISTANCESENSOR   = (0x28)
const CMD_GET_BALANCE_MODE     = (0x29)
const CMD_GET_LIGHT            = (0x2A)
const CMD_GET_BATTERY_LEVEL_H  = (0x2B)
const CMD_GET_BATTERY_LEVEL_L  = (0x2C)
const CMD_GET_ANGLE            = (0x2D)
const CMD_GET_ANGLE_ACC        = (0x2E)
const CMD_GET_DISTANCE         = (0x2F)


module.exports = {
    CMD_SET_TEST_VALUE: CMD_SET_TEST_VALUE,
    CMD_SET_MOVEMENT: CMD_SET_MOVEMENT,
    CMD_SET_SERVO_1_POSITION: CMD_SET_SERVO_1_POSITION,
    CMD_SET_SERVO_2_POSITION: CMD_SET_SERVO_2_POSITION,
    CMD_SET_BATTERY_ALARM: CMD_SET_BATTERY_ALARM,
    CMD_SET_PID_P_LEVEL: CMD_SET_PID_P_LEVEL,
    CMD_SET_PID_I_LEVEL: CMD_SET_PID_I_LEVEL,
    CMD_SET_PID_D_LEVEL: CMD_SET_PID_D_LEVEL,
    CMD_SET_DISTANCESENSOR: CMD_SET_DISTANCESENSOR, 
    CMD_SET_BALANCE_MODE: CMD_SET_BALANCE_MODE,
    CMD_SET_LIGHT: CMD_SET_LIGHT,

    CMD_GET_TEST_VALUE: CMD_GET_TEST_VALUE,
    CMD_GET_MOVEMENT: CMD_GET_MOVEMENT,
    CMD_GET_SERVO_1_POSITION: CMD_GET_SERVO_1_POSITION,
    CMD_GET_SERVO_2_POSITION: CMD_GET_SERVO_2_POSITION,
    CMD_GET_BATTERY_ALARM: CMD_GET_BATTERY_ALARM,
    CMD_GET_PID_P_LEVEL: CMD_GET_PID_P_LEVEL,
    CMD_GET_PID_I_LEVEL: CMD_GET_PID_I_LEVEL,
    CMD_GET_PID_D_LEVEL: CMD_GET_PID_D_LEVEL,
    CMD_GET_DISTANCESENSOR: CMD_GET_DISTANCESENSOR,
    CMD_GET_BALANCE_MODE: CMD_GET_BALANCE_MODE,
    CMD_GET_LIGHT: CMD_GET_LIGHT,
    CMD_GET_BATTERY_LEVEL_H: CMD_GET_BATTERY_LEVEL_H,
    CMD_GET_BATTERY_LEVEL_L: CMD_GET_BATTERY_LEVEL_L,
    CMD_GET_ANGLE: CMD_GET_ANGLE,
    CMD_GET_ANGLE_ACC: CMD_GET_ANGLE_ACC,
    CMD_GET_DISTANCE: CMD_GET_DISTANCE,
}
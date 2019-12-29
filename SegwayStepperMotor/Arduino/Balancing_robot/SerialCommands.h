//First byte is the command byte. 
//Bit 7 and 6 is command type
//Bit 5-0 is command sub-type
//|76|543210|
//Command type
//00xB = 0 -> Navigation
//01xB = 1 -> Set value
//10xB = 2 -> Get Value


#define CMD_TYPE_SET_VALUE       1
#define CMD_TYPE_GET_VALUE       2

#define TURN_LEFT_BIT        (0b00000001)
#define TURN_RIGHT_BIT       (0b00000010)
#define MOVE_FORWARD_BIT     (0b00000100)
#define MOVE_BACKWARDS_BIT   (0b00001000)

#define CMD_SET_TEST_VALUE         (0x00)
#define CMD_SET_MOVEMENT           (0x01)
#define CMD_SET_SERVO_1_POSITION   (0x02)
#define CMD_SET_SERVO_2_POSITION   (0x03)
#define CMD_SET_BATTERY_ALARM      (0x04)
#define CMD_SET_PID_P_LEVEL        (0x05)
#define CMD_SET_PID_I_LEVEL        (0x06)
#define CMD_SET_PID_D_LEVEL        (0x07)
#define CMD_SET_SELFBALANCE_LEVEL  (0x08)
#define CMD_SET_DISTANCESENSOR     (0x09)
#define CMD_SET_BALANCE_MODE       (0x0A)
#define CMD_SET_LIGHT              (0x0B)

#define CMD_GET_TEST_VALUE         (0x00)
#define CMD_GET_MOVEMENT           (0x01)
#define CMD_GET_SERVO_1_POSITION   (0x02)
#define CMD_GET_SERVO_2_POSITION   (0x03)
#define CMD_GET_BATTERY_ALARM      (0x04)
#define CMD_GET_PID_P_LEVEL        (0x05)
#define CMD_GET_PID_I_LEVEL        (0x06)
#define CMD_GET_PID_D_LEVEL        (0x07)
#define CMD_GET_SELFBALANCE_LEVEL  (0x08)
#define CMD_GET_DISTANCESENSOR     (0x09)
#define CMD_GET_BALANCE_MODE       (0x0A)
#define CMD_GET_LIGHT              (0x0B)
#define CMD_GET_BATTERY_LEVEL_H    (0x0C)
#define CMD_GET_BATTERY_LEVEL_L    (0x0D)
#define CMD_GET_ANGLE              (0x0E)
#define CMD_GET_ANGLE_ACC          (0x0F)
#define CMD_GET_DISTANCE           (0x10)
#define CMD_GET_SERVO_1_MIN        (0x11)
#define CMD_GET_SERVO_1_MAX        (0x12)
#define CMD_GET_SERVO_2_MIN        (0x13)
#define CMD_GET_SERVO_2_MAX        (0x14)

#define CMD_TYPE_SET_VALUE       1
#define CMD_TYPE_GET_VALUE       2

#define TURN_LEFT_BIT        (0b00000001)
#define TURN_RIGHT_BIT       (0b00000010)
#define MOVE_FORWARD_BIT     (0b00000100)
#define MOVE_BACKWARDS_BIT   (0b00001000)

#define CMD_SET_TEST_VALUE       (0x00)
#define CMD_SET_MOVEMENT         (0x01)
#define CMD_SET_SERVO_1_POSITION (0x02)
#define CMD_SET_SERVO_2_POSITION (0x03)
#define CMD_SET_BATTERY_ALARM    (0x04)
#define CMD_SET_PID_P_LEVEL      (0x05)
#define CMD_SET_PID_I_LEVEL      (0x06)
#define CMD_SET_PID_D_LEVEL      (0x07)
#define CMD_SET_DISTANCESENSOR   (0x08)
#define CMD_SET_ENABLE_BALANCE   (0x09)
#define CMD_SET_LIGHT            (0x0A)

#define CMD_GET_TEST_VALUE       (0x00)
#define CMD_GET_BATTERY_LEVEL    (0x01)
#define CMD_GET_ANGLE            (0x02)
#define CMD_GET_ANGLE_ACC        (0x03)
#define CMD_GET_DISTANCE         (0x04)

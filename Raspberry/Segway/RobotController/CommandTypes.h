#ifndef CommandTypes
#define CommandTypes

#define COMMAND_REPLY_FILTER         (0b01110000)
#define COMMAND_ID_FILTER            (0b00001111)

#define COMMAND_DATA_BYTE_NO_REPLY   (0x10)//(0b00010000) 
#define COMMAND_DATA_SHORT_NO_REPLY  (0x20)//(0b00100000)
#define COMMAND_NO_DATA_NO_REPLY     (0x30)//(0b00110000)
#define COMMAND_NO_DATA_BYTE_REPLY   (0x40)//(0b01000000)
#define COMMAND_NO_DATA_SHORT_REPLY  (0x50)//(0b01010000)
#define REPLY_BYTE                   (0x60)//(0b01100000)
#define REPLY_SHORT                  (0x70)//(0b01110000)

#endif
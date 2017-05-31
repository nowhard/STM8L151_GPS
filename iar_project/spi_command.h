#ifndef SPI_COMMAND_H
#define SPI_COMMAND_H

enum
{
    SET_TIME=0x1,
    GET_TIME,
    SET_ALARM,
    GET_ALARM,
    GET_STATUS,
    GET_BATTERY,
};

//CMD len in bytes

#define SET_TIME_CMD_LEN        6
#define GET_TIME_CMD_LEN        6
#define SET_ALARM_CMD_LEN       3
#define GET_ALARM_CMD_LEN       3
#define GET_STATUS_CMD_LEN      1
#define GET_BATTERY_CMD_LEN     2

#endif
#ifndef SPI_COMMAND_H
#define SPI_COMMAND_H

#define MAX_SPI_CMD_LEN         6

typedef enum
{
    SET_TIME=0x1,
    GET_TIME,
    SET_ALARM,
    GET_ALARM,
    GET_STATUS,
    GET_BATTERY,
    SET_SLEEP,
}enSPICommand;

typedef struct
{
  enSPICommand cmd;
  uint8_t cmdBuf[MAX_SPI_CMD_LEN];
  uint8_t bufCnt;
}stSPICommand

//CMD len in bytes

#define SET_TIME_CMD_LEN        6
#define GET_TIME_CMD_LEN        6
#define SET_ALARM_CMD_LEN       3
#define GET_ALARM_CMD_LEN       3
#define GET_STATUS_CMD_LEN      1
#define GET_BATTERY_CMD_LEN     2
#define SET_SLEEP_CMD_LEN       1

void SPI_Slave_Init(void);
void SPI_HandleCommand(stSPICommand *SPICommand);
void SPI_HandleInterrupt(stSPICommand *SPICommand);

#endif
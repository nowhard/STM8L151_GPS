#ifndef SPI_COMMAND_H
#define SPI_COMMAND_H

#define MAX_SPI_CMD_LEN         6

typedef enum
{
    CMD_NONE=0x0,
    SET_TIME=0x1,
    GET_TIME=0x2,
    SET_ALARM=0x3,
    GET_ALARM=0x4,
    GET_STATUS=0x5,
    GET_BATTERY=0x6,
    SET_SLEEP=0x7,
}enSPICommand;

typedef struct
{
  enSPICommand cmd;
  uint8_t cmdBuf[MAX_SPI_CMD_LEN];
  uint8_t bufCnt;
}stSPICommand;


//CMD len in bytes

#define SET_TIME_CMD_LEN        6
#define GET_TIME_CMD_LEN        6
#define SET_ALARM_CMD_LEN       3
#define GET_ALARM_CMD_LEN       3
#define GET_STATUS_CMD_LEN      1
#define GET_BATTERY_CMD_LEN     2
#define SET_SLEEP_CMD_LEN       1


#define SPI_NEED_HANDLE_CMD     1
#define SPI_NO_NEED_HANDLE_CMD  0

void SPI_Slave_Init(void);
void SPI_HandleCommand(stSPICommand *SPICommand);
uint8_t SPI_HandleInterrupt(stSPICommand *SPICommand);

#endif
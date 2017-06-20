#ifndef MAIN_H
#define MAIN_H


typedef enum
{
  WAKEUP_NONE=0x0,
  WAKEUP_RTC,
  WAKEUP_ACCEL,
  WAKEUP_BUTTON,
} enWakeUpSource;

typedef struct
{
  uint16_t batteryValue;
  enWakeUpSource wakeupSource;
  
} stDevParams;



typedef enum
{
   STATE_WAKEUP=0x1,
//   STATE_GET_VBAT,
//   STATE_GET_TIME,
   STATE_WAIT_COMMAND_PON,
   STATE_WAIT_COMMAND_POFF,
   STATE_HANDLE_COMMAND,
   STATE_HALT, 
}enStateMachine;


#endif
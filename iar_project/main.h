#ifndef MAIN_H
#define MAIN_H

#define PWR_SIM_PORT  GPIOB
#define PWR_SIM_PIN  GPIO_Pin_2 

#define PWR_GPS_PORT  GPIOB
#define PWR_GPS_PIN  GPIO_Pin_3 

#define PWR_KEY_PORT  GPIOB
#define PWR_KEY_PIN  GPIO_Pin_0 

#define SB_1_PORT  GPIOD
#define SB_1_PIN  GPIO_Pin_1 

#define SB_2_PORT  GPIOD
#define SB_2_PIN  GPIO_Pin_2 

#define ACCEL_INT_PORT GPIOD
#define ACCEL_INT_PIN  GPIO_Pin_3 
#define ACCEL_INT_EXTI EXTI_Pin_3

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
   STATE_WAIT_COMMAND,
   STATE_HANDLE_COMMAND,
   STATE_HALT, 
}enStateMachine;


#endif
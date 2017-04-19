
#include "stm8l15x.h"


#define POWER_GPRS_PORT  GPIOA
#define POWER_GPRS_PIN  GPIO_Pin_4 

#define POWER_GPS_PORT  GPIOA
#define POWER_GPS_PIN  GPIO_Pin_5 

#define ACCEL_INT_PORT GPIOA
#define ACCEL_INT_PIN  GPIO_Pin_6 
#define ACCEL_INT_EXTI EXTI_Pin_6

void Keys_Init(void);
void EXTI_Init(void);
void SPI_Accel_Init(void);


void main(void)
{
  Keys_Init();
  EXTI_Init();
  SPI_Accel_Init();
  while (1)
  {
    //GPIO_ToggleBits(LED_GPIO_PORT, LED_GPIO_PINS);
  }
}


void Keys_Init(void)
{
   GPIO_Init(POWER_GPRS_PORT, POWER_GPRS_PIN, GPIO_Mode_Out_PP_Low_Fast); 
   GPIO_Init(POWER_GPS_PORT, POWER_GPS_PIN, GPIO_Mode_Out_PP_Low_Fast); 
}

void EXTI_Init(void)
{
    GPIO_Init(ACCEL_INT_PORT, ACCEL_INT_PIN, GPIO_Mode_In_FL_IT);
    EXTI_SetPinSensitivity((EXTI_Pin_TypeDef)ACCEL_INT_EXTI, EXTI_Trigger_Falling);
}

void SPI_Accel_Init(void)
{
}


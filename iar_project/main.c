#include "stm8l15x.h"
#include "main.h"




void Keys_Init(void);
void EXTI_Init(void);
void ADC_Bat_Init(void);
void SPI_Accel_Init(void);


void main(void)
{
  Keys_Init();
  EXTI_Init();
  SPI_Accel_Init();
  ADC_Bat_Init();
  while (1)
  {
    //GPIO_ToggleBits(LED_GPIO_PORT, LED_GPIO_PINS);
  }
}

void Keys_Init(void)
{
   GPIO_Init(PWR_SIM_PORT, PWR_SIM_PIN, GPIO_Mode_Out_PP_Low_Fast); 
   GPIO_Init(PWR_GPS_PORT, PWR_GPS_PIN, GPIO_Mode_Out_PP_Low_Fast); 
   
   GPIO_Init(PWR_KEY_PORT, PWR_KEY_PIN, GPIO_Mode_Out_PP_Low_Fast); 
   GPIO_Init(SB_1_PORT, SB_1_PIN, GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(SB_2_PORT, SB_2_PIN, GPIO_Mode_Out_PP_Low_Fast);
}

void EXTI_Init(void)
{
    GPIO_Init(ACCEL_INT_PORT, ACCEL_INT_PIN, GPIO_Mode_In_FL_IT);
    EXTI_SetPinSensitivity((EXTI_Pin_TypeDef)ACCEL_INT_EXTI, EXTI_Trigger_Falling);
}

void SPI_Accel_Init(void)
{
}

void ADC_Bat_Init(void)
{
}


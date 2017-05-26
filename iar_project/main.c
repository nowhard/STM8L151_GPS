#include "stm8l15x.h"
#include "main.h"




void Keys_Init(void);
void EXTI_Init(void);
void ADC_Bat_Init(void);
void SPI_Slave_Init(void);
void RTC_WakeUp_Init(void);

void main(void)
{
  Keys_Init();
  EXTI_Init();
  RTC_WakeUp_Init();
  SPI_Slave_Init();
  ADC_Bat_Init();
  
  enableInterrupts();
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

void SPI_Slave_Init(void)
{
  SPI_Init(SPI1,SPI_FirstBit_MSB,SPI_BaudRatePrescaler_2,
           SPI_Mode_Slave,SPI_CPOL_High,SPI_CPHA_1Edge,
           SPI_Direction_2Lines_FullDuplex,SPI_NSS_Hard,0);
  
  
  
}

void ADC_Bat_Init(void)
{
}

void RTC_WakeUp_Init(void)
{
   CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
   
      //Настраиваем RTC
   RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16); //time_step = 488uS
   RTC_ITConfig(RTC_IT_WUT, ENABLE);

 
  // CFG->GCR |= CFG_GCR_AL; //Поднимаем флаг AL
   RTC_SetWakeUpCounter(2049);//Прерывание через каждую секунду
   RTC_WakeUpCmd(ENABLE);

 //  halt();по команде SIM800
}

INTERRUPT_HANDLER(EXTI3_Accel_IRQHandler, 11)
{

 EXTI_ClearITPendingBit (EXTI_IT_Pin3);
}


INTERRUPT_HANDLER(RTC_Wakeup_IRQHandler, 4)
{

// EXTI_ClearITPendingBit (EXTI_IT_Pin3);
}
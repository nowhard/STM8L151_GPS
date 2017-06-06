#include "stm8l15x.h"
#include "main.h"
#include "spi_command.h"
#include "power.h"
#include "adc_bat.h"
#include "rtc.h"
#include "external_signals.h"

enStateMachine StateMachine;
stDevParams DevParams;
stSPICommand SPICommand;




void CycleStateMachine(void);

void main(void)
{
  DevParams.wakeupSource=WAKEUP_NONE;
  StateMachine = STATE_WAIT_COMMAND;
  
  Buttons_Init();
  Modules_PowerInit();
  EXTI_Init();
  RTC_Calendar_Init();
  SPI_Slave_Init();
  ADC_Bat_Init();
  
  enableInterrupts();
  while (1)
  {
      CycleStateMachine();
  }
}

//-----------------------------------------------------------------------------
void CycleStateMachine(void)
{
    switch(StateMachine)
    {
        case STATE_WAKEUP:
        {
          //Считать параметры и время просыпания 
          
          //Разбудить модули
          Modules_PowerON();
        }
        break;
        
        case STATE_WAIT_COMMAND:
        {
        }
        break;
        
        case STATE_HANDLE_COMMAND:
        {
            SPI_HandleCommand(&SPICommand);
        }
        break;
        
        default:
        {
            
        }
    }
}
//-----------------------------------------------------------------------------
INTERRUPT_HANDLER(EXTI3_IRQHandler,11)
{
  //Запустить выполнение задачи с параметром-экстренное просыпание
  EXTI_ClearITPendingBit (EXTI_IT_Pin3);
  DevParams.wakeupSource=WAKEUP_ACCEL;
  
}


INTERRUPT_HANDLER(RTC_CSSLSE_IRQHandler,4)
{

 // RTC_ClearITPendingBit(RTC_IT_WUT); 
  //Запустить выполнение задачи с параметром-периодическое просыпание
  RTC_ClearITPendingBit(RTC_IT_ALRA); 
  DevParams.wakeupSource=WAKEUP_RTC;
}


INTERRUPT_HANDLER(SPI1_IRQHandler,26)
{
    SPI_ClearITPendingBit(SPI1,SPI_IT_RXNE); 
    SPI_HandleInterrupt(&SPICommand);    
}

//Необходимо ли просыпание от кнопки?
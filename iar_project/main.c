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
  
  GPIO_Unused_Init();
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
          //Считать параметры 
          DevParams.batteryValue=ADC_GetVcc();
          
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
           StateMachine=SPI_HandleCommand(&SPICommand);      
        }
        break;
        
        case STATE_HALT:
        {
            Modules_PowerOFF();
            StateMachine=STATE_WAIT_COMMAND;
            halt();
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
  //Запустить выполнение задачи с параметром-экстренное пробуждение
  EXTI_ClearITPendingBit (EXTI_IT_Pin3);
  DevParams.wakeupSource=WAKEUP_ACCEL;
  StateMachine=STATE_WAKEUP;
  
}


INTERRUPT_HANDLER(RTC_CSSLSE_IRQHandler,4)
{

 // RTC_ClearITPendingBit(RTC_IT_WUT); 
  //Запустить выполнение задачи с параметром-периодическое пробуждение
  RTC_ClearITPendingBit(RTC_IT_ALRA); 
  DevParams.wakeupSource=WAKEUP_RTC;
  StateMachine=STATE_WAKEUP;
}


INTERRUPT_HANDLER(SPI1_IRQHandler,26)
{
    SPI_ClearITPendingBit(SPI1,SPI_IT_RXNE); 
    if(SPI_HandleInterrupt(&SPICommand)==SPI_NEED_HANDLE_CMD)  
    {
        StateMachine=STATE_HANDLE_COMMAND;
    }
}

//Необходимо ли пробуждение от кнопки?
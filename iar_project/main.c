#include "stm8l15x.h"
#include "main.h"
#include "spi_command.h"

enStateMachine StateMachine;
stDevParams DevParams;
stSPICommand SPICommand;

void Keys_Init(void);
void EXTI_Init(void);
void ADC_Bat_Init(void);
void SPI_Slave_Init(void);
void RTC_WakeUp_Init(void);
void RTC_Calendar_Init(void);

uint16_t ADC_GetVcc(void);
void Modules_PowerON(void);
void Modules_PowerOFF(void);

void CycleStateMachine(void);

void main(void)
{
  DevParams.wakeupSource=WAKEUP_NONE;
  StateMachine = STATE_WAIT_COMMAND;
  
  Keys_Init();
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

//Подтянуть к GND неиспользуемые выводы

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
   CLK_PeripheralClockConfig(CLK_Peripheral_SPI1,ENABLE);
   SPI_Init(SPI1,SPI_FirstBit_MSB,SPI_BaudRatePrescaler_2,
           SPI_Mode_Slave,SPI_CPOL_High,SPI_CPHA_1Edge,
           SPI_Direction_2Lines_FullDuplex,SPI_NSS_Hard,0);
   
   SPI_ITConfig(SPI1,SPI_IT_RXNE,ENABLE);
   SPI_Cmd(SPI1,ENABLE); 
  
}

void ADC_Bat_Init(void)
{
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);
    ADC_Init(ADC1, ADC_ConversionMode_Single, ADC_Resolution_12Bit,ADC_Prescaler_2);
    ADC_VrefintCmd(ENABLE);
    ADC_Cmd(ADC1, ENABLE);
}

//void RTC_WakeUp_Init(void)
//{
//  
//   CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
//   CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);
//   
//      //Настраиваем RTC
//   RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits); 
//   RTC_ITConfig(RTC_IT_WUT, ENABLE);
//
// 
//  // CFG->GCR |= CFG_GCR_AL; //Поднимаем флаг AL
//   RTC_SetWakeUpCounter(2049);//Прерывание через каждую секунду
//   RTC_WakeUpCmd(ENABLE);
//
// //  halt();по команде SIM800
//}


void RTC_Calendar_Init(void)
{
  RTC_InitTypeDef   RTC_InitStr;
  RTC_TimeTypeDef   RTC_TimeStr;
  RTC_DateTypeDef   RTC_DateStr;
  RTC_AlarmTypeDef  RTC_AlarmStr;
  
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
  CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);
  
  RTC_InitStr.RTC_HourFormat = RTC_HourFormat_24;
  RTC_InitStr.RTC_AsynchPrediv = 0x7F;
  RTC_InitStr.RTC_SynchPrediv = 0x00FF;
  RTC_Init(&RTC_InitStr);

  RTC_DateStructInit(&RTC_DateStr);
  RTC_DateStr.RTC_WeekDay = RTC_Weekday_Sunday;
  RTC_DateStr.RTC_Date = 01;
  RTC_DateStr.RTC_Month = RTC_Month_January;
  RTC_DateStr.RTC_Year = 17;
  RTC_SetDate(RTC_Format_BIN, &RTC_DateStr);

  RTC_TimeStructInit(&RTC_TimeStr);
  RTC_TimeStr.RTC_Hours   = 00;
  RTC_TimeStr.RTC_Minutes = 00;
  RTC_TimeStr.RTC_Seconds = 00;
  RTC_SetTime(RTC_Format_BIN, &RTC_TimeStr);
  
  RTC_TimeStr.RTC_Hours   = 12;
  RTC_TimeStr.RTC_Minutes = 00;
  RTC_TimeStr.RTC_Seconds = 00;
  
  RTC_AlarmStr.RTC_AlarmTime = RTC_TimeStr;
  RTC_AlarmStr.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
  RTC_SetAlarm(RTC_Format_BIN, &RTC_AlarmStr);

  RTC_ITConfig(RTC_IT_ALRA, ENABLE);
  RTC_AlarmCmd(ENABLE);
}

__near __no_init const unsigned char Factory_VREFINT @ 0x4910;
uint16_t ADC_GetVcc(void)
{
 uint32_t tmp_value;
 uint32_t res;
 uint32_t factory_ref_voltage; 
 uint8_t count;

 ADC_ChannelCmd(ADC1, ADC_Channel_Vrefint, ENABLE);
  
  tmp_value = 0;
  for (count=0; count<16; count++)
  {
    ADC_SoftwareStartConv(ADC1);
    while (ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
    tmp_value += ADC_GetConversionValue(ADC1);
    if (count != 0) tmp_value = tmp_value >> 1;
  };  

  if (Factory_VREFINT != 0)
   factory_ref_voltage = 0x600+Factory_VREFINT;
  else
   factory_ref_voltage = 1671;
  
  res = (factory_ref_voltage*100*3)/tmp_value;
    
  ADC_ChannelCmd(ADC1, ADC_Channel_Vrefint, DISABLE);
  
  return (uint16_t)res; 
}


//-----------------------------------------------------------------------------
void Modules_PowerON(void)
{
    
}

void Modules_PowerOFF(void)
{
    
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
    if(SPICommand.bufCnt==0)
    {
      SPICommand.cmd=SPI_ReceiveData(SPI1);
      SPICommand.bufCnt++;
    }
    else
    {
        switch(SPICommand.cmd)
        {
          case SET_TIME:
          {
              
          }
          break;
          
          case SET_ALARM:
          {
            
          }
          break;
          
          case GET_TIME:
          {
            
          }
          break;
                  
          CASE GET_ALARM:
          {
          }
          BREAK; 
          
          CASE GET_BATTERY:
          {
          }
          BREAK;  
          
          CASE GET_STATUS:
          {
          }
          BREAK;    
          
          default:
          {
            
          }
          break;            
        }
    }
}

//Необходимо ли просыпание от кнопки?
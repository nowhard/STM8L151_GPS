#include "stm8l15x.h"
#include "spi_command.h"
#include "main.h"
#include "power.h"

RTC_TimeTypeDef   RTC_TimeStr;
RTC_DateTypeDef   RTC_DateStr;
RTC_AlarmTypeDef  RTC_AlarmStr;
extern stDevParams DevParams;

void SPI_Slave_Init(void)
{
   CLK_PeripheralClockConfig(CLK_Peripheral_SPI1,ENABLE);
   SPI_Init(SPI1,SPI_FirstBit_MSB,SPI_BaudRatePrescaler_2,
           SPI_Mode_Slave,SPI_CPOL_High,SPI_CPHA_1Edge,
           SPI_Direction_2Lines_FullDuplex,SPI_NSS_Hard,0);
   
   SPI_ITConfig(SPI1,SPI_IT_RXNE,ENABLE);
   SPI_Cmd(SPI1,ENABLE); 
  
}

enStateMachine SPI_HandleCommand(stSPICommand *SPICommand)
{
    switch(SPICommand->cmd)
    {
        case SET_TIME:
        {
            RTC_TimeStr.RTC_Hours=SPICommand->cmdBuf[0];
            RTC_TimeStr.RTC_Minutes=SPICommand->cmdBuf[1];
            RTC_TimeStr.RTC_Seconds=SPICommand->cmdBuf[2];
            
            RTC_DateStr.RTC_Year=SPICommand->cmdBuf[3];
            RTC_DateStr.RTC_Month=SPICommand->cmdBuf[4];
            RTC_DateStr.RTC_Day=SPICommand->cmdBuf[5];
            
            RTC_SetTime(RTC_Format_BIN, &RTC_TimeStr);
            RTC_SetDate(RTC_Format_BIN, &RTC_DateStr);
        }
        break;
        
        case SET_ALARM:
        {
            RTC_AlarmStr.RTC_Hours=SPICommand->cmdBuf[0];
            RTC_AlarmStr.RTC_Minutes=SPICommand->cmdBuf[1];
            RTC_AlarmStr.RTC_Seconds=SPICommand->cmdBuf[2];
            
            RTC_SetAlarm(RTC_Format_BIN, &RTC_AlarmStr);
        }
        break;
        
        case SET_SLEEP:
        {
           return STATE_HALT       
        }
        break;
        
//        case GET_TIME:
//        {
//          
//        }
//        break;
                
//        case GET_ALARM:
//        {
//        }
//        break; 
//        
//        case GET_BATTERY:
//        {
//        }
//        break;  
//        
//        case GET_STATUS:
//        {
//        }
//        break;    
        
        default:
        {
          
        }
        break;
    }
    
    return STATE_WAIT_COMMAND;
}

uint8_t SPI_HandleInterrupt(stSPICommand *SPICommand)
{
      if(SPICommand->bufCnt==0)
    {
      SPICommand->cmd=SPI_ReceiveData(SPI1);
      SPICommand->bufCnt++;
    }
    else
    {
        switch(SPICommand->cmd)
        {
//          case SET_TIME:
//          {
//              
//          }
//          break;
//          
//          case SET_ALARM:
//          {
//            
//          }
//          break;
          
          case GET_TIME:
          {
              while(RTC_WaitForSynchro() != SUCCESS);
              RTC_GetTime(RTC_Format_BIN, &RTC_TimeStr);
              RTC_GetDate(RTC_Format_BIN, &RTC_DateStr);
              SPICommand->cmdBuf[0]=RTC_TimeStr.RTC_Hours;
              SPICommand->cmdBuf[1]=RTC_TimeStr.RTC_Minutes;
              SPICommand->cmdBuf[2]=RTC_TimeStr.RTC_Seconds;
              SPICommand->cmdBuf[3]=RTC_DateStr.RTC_Year;
              SPICommand->cmdBuf[4]=RTC_DateStr.RTC_Month;
              SPICommand->cmdBuf[5]=RTC_DateStr.RTC_Date;
          }
          break;
                  
          case GET_ALARM:
          {
              RTC_GetAlarm(RTC_Format_BIN, &RTC_AlarmStr);
              SPICommand->cmdBuf[0]=RTC_AlarmStr.RTC_AlarmTime.RTC_Hours;
              SPICommand->cmdBuf[1]=RTC_AlarmStr.RTC_AlarmTime.RTC_Minutes;
              SPICommand->cmdBuf[2]=RTC_AlarmStr.RTC_AlarmTime.RTC_Seconds;
          }
          break; 
          
          case GET_BATTERY:
          {
              *(uint16_t*)(&SPICommand->cmdBuf[0])=DevParams.batteryValue;
          }
          break;  
          
          case GET_STATUS:
          {
              SPICommand->cmdBuf[0]=DevParams.wakeupSource;
          }
          break;    
          
          default:
          {
              return SPI_NEED_HANDLE_CMD;
          }
          break;            
        }
    }
    
    return SPI_NO_NEED_HANDLE_CMD;
}
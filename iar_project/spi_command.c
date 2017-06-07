#include "stm8l15x.h"
#include "spi_command.h"


void SPI_Slave_Init(void)
{
   CLK_PeripheralClockConfig(CLK_Peripheral_SPI1,ENABLE);
   SPI_Init(SPI1,SPI_FirstBit_MSB,SPI_BaudRatePrescaler_2,
           SPI_Mode_Slave,SPI_CPOL_High,SPI_CPHA_1Edge,
           SPI_Direction_2Lines_FullDuplex,SPI_NSS_Hard,0);
   
   SPI_ITConfig(SPI1,SPI_IT_RXNE,ENABLE);
   SPI_Cmd(SPI1,ENABLE); 
  
}

void SPI_HandleCommand(stSPICommand *SPICommand)
{
    switch(SPICommand->cmd)
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
}

void SPI_HandleInterrupt(stSPICommand *SPICommand)
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
                  
          case GET_ALARM:
          {
          }
          break; 
          
          case GET_BATTERY:
          {
          }
          break;  
          
          case GET_STATUS:
          {
          }
          break;    
          
          default:
          {
            
          }
          break;            
        }
    }
}
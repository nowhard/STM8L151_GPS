#include "spi_command.h"

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
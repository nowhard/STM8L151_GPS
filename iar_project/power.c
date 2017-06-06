#include "power.h"
#include "stm8l15x.h"

void Modules_PowerInit(void)
{
   GPIO_Init(PWR_SIM_PORT, PWR_SIM_PIN, GPIO_Mode_Out_PP_Low_Fast); 
   GPIO_Init(PWR_GPS_PORT, PWR_GPS_PIN, GPIO_Mode_Out_PP_Low_Fast);    
   GPIO_Init(PWR_KEY_PORT, PWR_KEY_PIN, GPIO_Mode_Out_PP_Low_Fast); 
}

void Modules_PowerON(void)
{
    
}

void Modules_PowerOFF(void)
{
    
}
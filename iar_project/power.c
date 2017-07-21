#include "power.h"
#include "stm8l15x.h"
#include "delay.h"

void Modules_PowerInit(void)
{
   GPIO_Init(PWR_SIM_PORT, PWR_SIM_PIN, GPIO_Mode_Out_PP_Low_Fast); 
   GPIO_Init(PWR_GPS_PORT, PWR_GPS_PIN, GPIO_Mode_Out_PP_Low_Fast);    
   GPIO_Init(PWR_KEY_PORT, PWR_KEY_PIN, GPIO_Mode_Out_OD_HiZ_Slow); 
   
   GPIO_WriteBit(PWR_SIM_PORT,PWR_SIM_PIN,RESET);
   GPIO_WriteBit(PWR_GPS_PORT,PWR_GPS_PIN,RESET);
   //GPIO_WriteBit(PWR_GPS_PORT,PWR_GPS_PIN,SET);
   GPIO_WriteBit(PWR_KEY_PORT,PWR_KEY_PIN,SET); 
   
   
   //pwr stat
   GPIO_Init(PWR_STAT_SIM_PORT, PWR_STAT_SIM_PIN, GPIO_Mode_In_FL_No_IT); 
   GPIO_WriteBit(PWR_STAT_SIM_PORT,PWR_STAT_SIM_PIN,RESET);
}

#define DELAY_SIM_POWER_START   1500
#define DELAY_SIM_POWER_STOP   200
#define DELAY_SIM_ON_OFF        2500

void Modules_PowerON(void)
{
  GPIO_WriteBit(PWR_KEY_PORT,PWR_KEY_PIN,SET);  
  GPIO_WriteBit(PWR_SIM_PORT,PWR_SIM_PIN,SET);
  delay_ms(DELAY_SIM_POWER_START);
  GPIO_WriteBit(PWR_KEY_PORT,PWR_KEY_PIN,RESET); 
  delay_ms(DELAY_SIM_ON_OFF);
  GPIO_WriteBit(PWR_KEY_PORT,PWR_KEY_PIN,SET);    
}

void Modules_PowerOFF(void)
{
  GPIO_WriteBit(PWR_KEY_PORT,PWR_KEY_PIN,RESET); 
  delay_ms(DELAY_SIM_ON_OFF);
  GPIO_WriteBit(PWR_KEY_PORT,PWR_KEY_PIN,SET);  
  delay_ms(DELAY_SIM_POWER_STOP);
  GPIO_WriteBit(PWR_SIM_PORT,PWR_SIM_PIN,RESET);
}
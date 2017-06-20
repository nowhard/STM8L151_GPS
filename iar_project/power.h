#ifndef POWER_H
#define POWER_H

#define PWR_STAT_SIM_PORT  GPIOB
#define PWR_STAT_SIM_PIN   GPIO_Pin_1 

#define PWR_SIM_PORT  GPIOB
#define PWR_SIM_PIN  GPIO_Pin_2 

#define PWR_GPS_PORT  GPIOB
#define PWR_GPS_PIN  GPIO_Pin_3 

#define PWR_KEY_PORT  GPIOB
#define PWR_KEY_PIN  GPIO_Pin_0 

void Modules_PowerInit(void);
void Modules_PowerON(void);
void Modules_PowerOFF(void);

#endif
#ifndef EXTERNAL_SIGNALS_H
#define EXTERNAL_SIGNALS_H



#define SB_1_PORT  GPIOD
#define SB_1_PIN  GPIO_Pin_1 

#define SB_2_PORT  GPIOD
#define SB_2_PIN  GPIO_Pin_2 

#define ACCEL_INT_PORT GPIOD
#define ACCEL_INT_PIN  GPIO_Pin_3 
#define ACCEL_INT_EXTI EXTI_Pin_3


void Buttons_Init(void);
void EXTI_Init(void);

#endif
#ifndef EXTERNAL_SIGNALS_H
#define EXTERNAL_SIGNALS_H

#include "stm8l15x.h"

#define SB_1_PORT  GPIOD
#define SB_1_PIN  GPIO_Pin_1 

#define SB_2_PORT  GPIOD
#define SB_2_PIN  GPIO_Pin_2 

#define ACCEL_INT_PORT GPIOD
#define ACCEL_INT_PIN  GPIO_Pin_3 
#define ACCEL_INT_EXTI EXTI_Pin_3

enum
{
    BUTTON_NOT_PRESSED=0,
    BUTTON_1_PRESSED=1,
    BUTTON_2_PRESSED=2,
    BUTTON_3_PRESSED=3,
};


void Buttons_Init(void);
void GPIO_Unused_Init(void);
void EXTI_Init(void);
uint8_t Button_Pressed(void);
#endif
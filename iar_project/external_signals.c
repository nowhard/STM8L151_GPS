#include "external_signals.h"
#include "stm8l15x.h"
#include "delay.h"

//Подтянуть к GND неиспользуемые выводы



void Buttons_Init(void)
{

   GPIO_Init(SB_1_PORT, SB_1_PIN, GPIO_Mode_In_PU_No_IT);
   GPIO_Init(SB_2_PORT, SB_2_PIN, GPIO_Mode_In_PU_No_IT);
}

uint8_t last_button=BUTTON_NOT_PRESSED;
uint8_t Button_Pressed(void)
{
    if((GPIO_ReadInputDataBit(SB_1_PORT, SB_1_PIN)==RESET) && (last_button==BUTTON_NOT_PRESSED))
    {
        delay_us(10);
        if((GPIO_ReadInputDataBit(SB_1_PORT, SB_1_PIN)==RESET)&& (last_button==BUTTON_NOT_PRESSED))
        {
          last_button= BUTTON_1_PRESSED; 
          return BUTTON_1_PRESSED;
        }
    }
    
    if((GPIO_ReadInputDataBit(SB_2_PORT, SB_2_PIN)==RESET)&& (last_button==BUTTON_NOT_PRESSED))
    {
        delay_us(10);
        if((GPIO_ReadInputDataBit(SB_2_PORT, SB_2_PIN)==RESET)&& (last_button==BUTTON_NOT_PRESSED))
        {
          last_button= BUTTON_2_PRESSED;   
          return BUTTON_2_PRESSED;
        }
    }
    
    last_button=BUTTON_NOT_PRESSED;
    return BUTTON_NOT_PRESSED;
}

void GPIO_Unused_Init(void)
{
    GPIO_Init(GPIOA, GPIO_Pin_All, GPIO_Mode_Out_PP_High_Slow);
    GPIO_Init(GPIOB, GPIO_Pin_All, GPIO_Mode_Out_PP_High_Slow);
    GPIO_Init(GPIOC, GPIO_Pin_All, GPIO_Mode_Out_PP_High_Slow);
    GPIO_Init(GPIOD, GPIO_Pin_All, GPIO_Mode_Out_PP_High_Slow);
}

void EXTI_Init(void)
{
    GPIO_Init(ACCEL_INT_PORT, ACCEL_INT_PIN, GPIO_Mode_In_FL_IT);
    EXTI_SetPinSensitivity((EXTI_Pin_TypeDef)ACCEL_INT_EXTI, EXTI_Trigger_Falling);
}
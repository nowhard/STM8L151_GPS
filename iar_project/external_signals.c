#include "external_signals.h"
#include "stm8l15x.h"

//Подтянуть к GND неиспользуемые выводы

void Buttons_Init(void)
{

   GPIO_Init(SB_1_PORT, SB_1_PIN, GPIO_Mode_Out_PP_Low_Fast);
   GPIO_Init(SB_2_PORT, SB_2_PIN, GPIO_Mode_Out_PP_Low_Fast);
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
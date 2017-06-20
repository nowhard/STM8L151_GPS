#include "delay.h"
#include "stm8l15x.h"

void delay_ms(uint32_t time)
{
    uint32_t cnt=time*(HSI_VALUE/80000);
    while(cnt--);
}

void delay_us(uint32_t time)
{
    uint32_t cnt=time*(HSI_VALUE/8000000);
    while(cnt--);
}
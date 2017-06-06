#include "adc_bat.h"
#include "stm8l15x.h"

void ADC_Bat_Init(void)
{
    CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);
    ADC_Init(ADC1, ADC_ConversionMode_Single, ADC_Resolution_12Bit,ADC_Prescaler_2);
    ADC_VrefintCmd(ENABLE);
    ADC_Cmd(ADC1, ENABLE);
}

__near __no_init const unsigned char Factory_VREFINT @ 0x4910;
uint16_t ADC_GetVcc(void)
{
 uint32_t tmp_value;
 uint32_t res;
 uint32_t factory_ref_voltage; 
 uint8_t count;

 ADC_ChannelCmd(ADC1, ADC_Channel_Vrefint, ENABLE);
  
  tmp_value = 0;
  for (count=0; count<16; count++)
  {
    ADC_SoftwareStartConv(ADC1);
    while (ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
    tmp_value += ADC_GetConversionValue(ADC1);
    if (count != 0) tmp_value = tmp_value >> 1;
  };  

  if (Factory_VREFINT != 0)
   factory_ref_voltage = 0x600+Factory_VREFINT;
  else
   factory_ref_voltage = 1671;
  
  res = (factory_ref_voltage*100*3)/tmp_value;
    
  ADC_ChannelCmd(ADC1, ADC_Channel_Vrefint, DISABLE);
  
  return (uint16_t)res; 
}
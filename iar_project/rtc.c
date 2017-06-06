#include "rtc.h"
#include "stm8l15x.h"


//void RTC_WakeUp_Init(void)
//{
//  
//   CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
//   CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);
//   
//      //Настраиваем RTC
//   RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits); 
//   RTC_ITConfig(RTC_IT_WUT, ENABLE);
//
// 
//  // CFG->GCR |= CFG_GCR_AL; //Поднимаем флаг AL
//   RTC_SetWakeUpCounter(2049);//Прерывание через каждую секунду
//   RTC_WakeUpCmd(ENABLE);
//
// //  halt();по команде SIM800
//}


void RTC_Calendar_Init(void)
{
  RTC_InitTypeDef   RTC_InitStr;
  RTC_TimeTypeDef   RTC_TimeStr;
  RTC_DateTypeDef   RTC_DateStr;
  RTC_AlarmTypeDef  RTC_AlarmStr;
  
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
  CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);
  
  RTC_InitStr.RTC_HourFormat = RTC_HourFormat_24;
  RTC_InitStr.RTC_AsynchPrediv = 0x7F;
  RTC_InitStr.RTC_SynchPrediv = 0x00FF;
  RTC_Init(&RTC_InitStr);

  RTC_DateStructInit(&RTC_DateStr);
  RTC_DateStr.RTC_WeekDay = RTC_Weekday_Sunday;
  RTC_DateStr.RTC_Date = 01;
  RTC_DateStr.RTC_Month = RTC_Month_January;
  RTC_DateStr.RTC_Year = 17;
  RTC_SetDate(RTC_Format_BIN, &RTC_DateStr);

  RTC_TimeStructInit(&RTC_TimeStr);
  RTC_TimeStr.RTC_Hours   = 00;
  RTC_TimeStr.RTC_Minutes = 00;
  RTC_TimeStr.RTC_Seconds = 00;
  RTC_SetTime(RTC_Format_BIN, &RTC_TimeStr);
  
  RTC_TimeStr.RTC_Hours   = 12;
  RTC_TimeStr.RTC_Minutes = 00;
  RTC_TimeStr.RTC_Seconds = 00;
  
  RTC_AlarmStr.RTC_AlarmTime = RTC_TimeStr;
  RTC_AlarmStr.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay;
  RTC_SetAlarm(RTC_Format_BIN, &RTC_AlarmStr);

  RTC_ITConfig(RTC_IT_ALRA, ENABLE);
  RTC_AlarmCmd(ENABLE);
}

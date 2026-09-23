#include "battery_app.h"
#include "battery_monitor.h"
#include "battery_sensors.h"
#include "app_config.h"
#include "main.h"
#include "adc.h"
#include "usart.h"
#include <stdio.h>

static BatteryConfig_t battery_cfg={12.0f,12.60f,9.60f,7.0f,8.0f,50.0f,20.0f};
static BatterySensorConfig_t sensor_cfg={3.3f,4095U,5.0f,1.650f,0.100f,10000.0f,10000.0f,3950.0f,298.15f};

void Battery_App_Init(void){
 Battery_Init(&battery_cfg);
 Sensors_Init(&sensor_cfg);
 const char msg[]="STM32 Intelligent Battery Health Monitor\r\n";
 HAL_UART_Transmit(&huart2,(uint8_t*)msg,(uint16_t)(sizeof(msg)-1U),100);
}

void Battery_App_Task(void){
 uint16_t raw[3]={0};
 HAL_ADC_Start(&hadc1);
 for(uint8_t i=0;i<3U;i++){
  if(HAL_ADC_PollForConversion(&hadc1,50)==HAL_OK) raw[i]=(uint16_t)HAL_ADC_GetValue(&hadc1);
 }
 HAL_ADC_Stop(&hadc1);
 float v=Sensors_ConvertBatteryVoltage(raw[0]);
 float i=Sensors_ConvertCurrent(raw[1]);
 float t=Sensors_ConvertTemperature(raw[2]);
 Battery_Update(v,i,t,(float)BATTERY_MONITOR_SAMPLE_PERIOD_MS/1000.0f);
 BatteryData_t d=Battery_GetData();
 char msg[192];
 int n=snprintf(msg,sizeof(msg),"V=%.2fV I=%.2fA T=%.1fC SoC=%.1f%% dV=%.3fV/min Rem=%.2fAh Status=%s\r\n",d.voltage_v,d.current_a,d.temperature_c,d.soc_percent,d.voltage_trend_v_per_min,d.remaining_capacity_ah,Battery_StatusString(d.status));
 if(n>0) HAL_UART_Transmit(&huart2,(uint8_t*)msg,(uint16_t)n,100);
}

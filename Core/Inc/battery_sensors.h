#ifndef BATTERY_SENSORS_H
#define BATTERY_SENSORS_H
#include <stdint.h>
typedef struct {float adc_vref;uint16_t adc_max;float voltage_divider_ratio;float current_sensor_zero_v;float current_sensor_sensitivity_v_per_a;float ntc_r_fixed_ohm;float ntc_r0_ohm;float ntc_beta;float ntc_t0_kelvin;} BatterySensorConfig_t;
void Sensors_Init(const BatterySensorConfig_t *config);
float Sensors_ConvertBatteryVoltage(uint16_t adc_raw);
float Sensors_ConvertCurrent(uint16_t adc_raw);
float Sensors_ConvertTemperature(uint16_t adc_raw);
#endif

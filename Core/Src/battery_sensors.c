#include "battery_sensors.h"
#include <math.h>
static BatterySensorConfig_t cfg;
void Sensors_Init(const BatterySensorConfig_t *config){if(config)cfg=*config;}
static float adc_to_voltage(uint16_t raw){return ((float)raw*cfg.adc_vref)/(float)cfg.adc_max;}
float Sensors_ConvertBatteryVoltage(uint16_t raw){return adc_to_voltage(raw)*cfg.voltage_divider_ratio;}
float Sensors_ConvertCurrent(uint16_t raw){float v=adc_to_voltage(raw);if(cfg.current_sensor_sensitivity_v_per_a<=0.0f)return 0.0f;return (v-cfg.current_sensor_zero_v)/cfg.current_sensor_sensitivity_v_per_a;}
float Sensors_ConvertTemperature(uint16_t raw){float v=adc_to_voltage(raw);if(v<=0.001f||v>=cfg.adc_vref-0.001f)return -273.15f;float r=(v*cfg.ntc_r_fixed_ohm)/(cfg.adc_vref-v);float inv_t=(1.0f/cfg.ntc_t0_kelvin)+(1.0f/cfg.ntc_beta)*logf(r/cfg.ntc_r0_ohm);return (1.0f/inv_t)-273.15f;}

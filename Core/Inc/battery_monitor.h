#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H
#include <stdint.h>
typedef enum { BATTERY_STATUS_OK=0, BATTERY_STATUS_LOW, BATTERY_STATUS_OVERVOLTAGE, BATTERY_STATUS_OVERTEMP, BATTERY_STATUS_OVERCURRENT } BatteryStatus_t;
typedef struct { float voltage_v; float current_a; float temperature_c; float soc_percent; float voltage_trend_v_per_min; float remaining_capacity_ah; BatteryStatus_t status; } BatteryData_t;
typedef struct { float nominal_voltage_v; float full_voltage_v; float empty_voltage_v; float capacity_ah; float max_current_a; float max_temperature_c; float low_soc_percent; } BatteryConfig_t;
void Battery_Init(const BatteryConfig_t *config);
void Battery_Update(float voltage_v,float current_a,float temperature_c,float dt_seconds);
BatteryData_t Battery_GetData(void);
const char *Battery_StatusString(BatteryStatus_t status);
#endif

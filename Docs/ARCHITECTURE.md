# System Architecture

Battery pack -> voltage divider -> STM32 ADC
Load current -> current sensor -> STM32 ADC
NTC thermistor -> divider -> STM32 ADC

ADC signals -> sensor conversion -> battery health logic -> UART telemetry

Health logic provides:
- Voltage-based SoC
- Voltage trend (dV/dt)
- Remaining-capacity estimate
- Low SoC, overvoltage, overcurrent and overtemperature flags

Firmware layers:
- HAL/CubeMX: MCU peripheral initialization
- Sensor layer: ADC counts to physical units
- Battery monitor: health calculations and fault state
- Application: periodic sampling and UART output

This is a monitoring demonstrator, not a certified BMS.

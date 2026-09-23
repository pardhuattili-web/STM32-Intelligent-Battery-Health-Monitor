# STM32 Intelligent Battery Health Monitor

A compact STM32 embedded battery-monitoring demonstrator that samples battery voltage, load current, and temperature, then derives state-of-charge, voltage trend, remaining-capacity estimate, and abnormal-condition flags.

## Features
- 3-channel ADC measurement pipeline
- Battery voltage sensing through a resistor divider
- Analog current-sensor conversion
- 10 kOhm NTC temperature estimation using the Beta equation
- Voltage-based SoC estimate
- Voltage trend (dV/dt)
- Simple current-integration capacity estimate
- Low-SoC, overvoltage, overcurrent, and overtemperature detection
- UART telemetry
- Modular Embedded C architecture

## Reference hardware
- STM32 development board
- 12 V-class / 3S battery for the example thresholds
- Resistor divider for voltage sensing
- Analog current sensor
- 10 kOhm NTC + 10 kOhm resistor
- USB-UART connection

## ADC example

| Channel | Measurement | Example conditioning |
|---|---|---|
| ADC1 CH1 | Battery voltage | 5:1 divider |
| ADC1 CH2 | Load current | 1.65 V zero, 100 mV/A |
| ADC1 CH3 | Temperature | 10 kOhm NTC divider |

The reference assumes a 12-bit ADC and 3.3 V reference. Adapt constants to the exact MCU, board and sensors.

## Firmware architecture
Battery -> ADC -> Sensor conversion -> Battery health logic -> UART telemetry

Health logic provides SoC, dV/dt, remaining capacity and fault status. See Docs/ARCHITECTURE.md for the detailed flow.

## CubeIDE integration
Create an STM32CubeIDE project for the exact MCU and configure ADC1 with three analog channels, USART2 at 115200 baud, and HAL/SysTick timing. Add the supplied Core/Inc and Core/Src files to the project.

Call the application layer once during startup and once per second from the main loop:

    Battery_App_Init();

    while (1)
    {
        Battery_App_Task();
        HAL_Delay(BATTERY_MONITOR_SAMPLE_PERIOD_MS);
    }

The application layer is intentionally separated from generated CubeMX code so it can be ported to different STM32 families.

## Example telemetry
    STM32 Intelligent Battery Health Monitor
    V=12.24V I=1.80A T=28.4C SoC=88.0% dV=-0.024V/min Rem=6.99Ah Status=OK

## Engineering notes
The SoC calculation is a simple voltage-window estimate, not a chemistry-specific estimator. The remaining-capacity calculation is an educational coulomb-counting approximation. A production BMS needs calibration, filtering, charge/discharge direction handling, temperature compensation, battery characterization, independent protection and robust fault recovery.

Never connect a battery pack directly to an MCU ADC input. Use an appropriately rated divider and protection network.

## Validation
See Docs/TEST_PLAN.md for nominal, low-voltage, overvoltage, overcurrent, overtemperature, voltage-trend and capacity tests.

## Portfolio value
This project demonstrates STM32 ADC interfacing, analog sensor conversion, Embedded C modularity, periodic real-time acquisition, state estimation, fault detection and UART diagnostics.

## Future upgrades
- DMA-based ADC acquisition
- Moving-average / low-pass filtering
- OLED or LCD display
- CAN telemetry for EV-oriented systems
- Flash logging
- Temperature-compensated SoC
- OCV/SoC lookup table
- FreeRTOS task separation
- Persistent diagnostics and event counters

## Author
Pardhasaradhi / Prem
ECE | Embedded Systems

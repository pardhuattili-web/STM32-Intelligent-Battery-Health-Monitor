# Test Plan

| Test | Input | Expected |
|---|---|---|
| Nominal | 12.0 V, 1 A, 25 C | OK |
| Low voltage | 9.6 V, 1 A, 25 C | LOW |
| Overvoltage | 12.8 V, 1 A, 25 C | OVERVOLTAGE |
| Overcurrent | 12.0 V, 9 A, 25 C | OVERCURRENT |
| Overtemperature | 12.0 V, 1 A, 55 C | OVERTEMP |
| Voltage trend | 12.2 V -> 11.8 V | Negative dV/dt |
| Capacity | 2 A for 1800 s | About 1 Ah consumed |

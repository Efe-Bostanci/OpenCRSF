# Firmware

This directory contains the application firmware for OpenCRSF.

## Target

- **MCU:** ESP32-C3 SuperMini
- **Framework:** Arduino
- **Receiver protocol:** CRSF
- **CRSF UART:** 420000 baud
- **PWM outputs:** 6
- **PWM frequency:** 50 Hz

## Firmware / hardware relationship

The firmware currently in this repository is the **V1 firmware**.

The same application logic is intended to run on **V2**. V2 changes the power distribution and protection circuitry rather than the CRSF-to-PWM control architecture.

Do not interpret the firmware directory as a V2 hardware revision.

## Source organization

The original development build contains the following application-level source files:

- `config.h`
- `crc.cpp`
- `crc.h`
- `crsf.cpp`
- `crsf.h`
- `failsafe.cpp`
- `failsafe.h`
- `OpenCRSF.ino.cpp`
- `servo.cpp`
- `servo.h`

Generated Arduino build files such as `.o`, `.d`, compiled libraries and binaries are not source files and should not be committed.

## Behaviour

At runtime the firmware:

1. receives CRSF data over UART
2. parses incoming frames
3. validates frame integrity
4. maps receiver channels to six PWM outputs
5. generates 50 Hz servo signals
6. enters the configured failsafe state when the receiver signal is lost
7. provides serial diagnostics for development and debugging

The exact source tree will be expanded when the cleaned source files are available.

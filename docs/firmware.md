# Firmware documentation

## Signal path

The firmware sits between the ELRS receiver and conventional PWM devices.

```text
ELRS receiver
     │
     │ CRSF
     ▼
ESP32-C3 SuperMini
     │
     ├── PWM CH1
     ├── PWM CH2
     ├── PWM CH3
     ├── PWM CH4
     ├── PWM CH5
     └── PWM CH6
```

## Communication

The receiver interface uses UART at **420000 baud** for CRSF communication.

The application is designed around a non-blocking main loop so receiver processing, failsafe checks and PWM updates can continue without unnecessary delays.

## Failsafe

When valid receiver frames stop arriving, the firmware uses predefined failsafe output positions rather than leaving the outputs uncontrolled.

The implementation also exposes diagnostic information during development, including frame counts, CRC errors and signal-loss timing.

## Diagnostics

Serial diagnostics are intended for development and troubleshooting. They are useful when verifying:

- whether CRSF frames are being received
- whether CRC errors are occurring
- whether the receiver signal has been lost
- what PWM values are being generated

## Revision rule

**Firmware revision and hardware revision are not the same thing.**

The current firmware is V1 firmware. It is also intended to operate on V2.

V2's main changes are on the power/protection side.

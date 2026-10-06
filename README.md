# OpenCRSF

**OpenCRSF** is a custom RC receiver project built around an **ESP32-C3 SuperMini**. It reads an ExpressLRS receiver's **CRSF** data over UART and converts it into **6 standard PWM outputs** for servos and ESCs.

The project started while I was working on an RC car and grew into a custom board focused on both signal conversion and power protection.

## What it does

```text
RadioMaster
    │
    ▼
ExpressLRS receiver
    │
    │ CRSF / UART
    ▼
ESP32-C3 SuperMini
    │
    ├── CH1 PWM
    ├── CH2 PWM
    ├── CH3 PWM  → ESC / throttle
    ├── CH4 PWM
    ├── CH5 PWM
    └── CH6 PWM
```

The firmware handles CRSF frame parsing, channel mapping, PWM generation and failsafe behaviour.

## Why I started it

I was working on an RC car that was controlled with a FlySky FC-CT6B. I wanted to use my RadioMaster transmitter instead, together with an ELRS receiver.

That created a simple hardware problem: the receiver outputs CRSF data, while the servos and ESC expect standard PWM.

I looked for CRSF-to-PWM converters, but they were expensive and not easy to find, so I decided to build one myself.

The first prototype was built on perfboard. It worked and could control 6 servos and a motor. During a later test, connecting the BEC resulted in the ELRS receiver being destroyed.

Instead of only replacing the receiver, I continued the project around the power side. OpenCRSF is now being developed as a board that can handle the CRSF-to-PWM conversion while also protecting the receiver, ESP32 and servo system from power related problems.

## Hardware revisions

### V1

The first working revision.

The prototype was able to control:

- 6 PWM channels
- 6 servos
- a brushless motor / ESC

V1 was tested successfully with a single ESC/BEC. During a later full power test with a higher current ESC and a larger motor, the ELRS receiver overheated and was permanently damaged.

The V1 power section used a PTC fuse, a TVS diode and bulk capacitors, but it did not provide enough isolation for the electronics branch and had no reverse polarity protection.

### V2

V2 focuses on separating the high current servo power path from the sensitive electronics.

The V2 hardware architecture is being redesigned around the power and protection section. It should be documented from the actual EasyEDA schematic rather than represented by a simplified block diagram.

- a shared `VBUS` for the six servo connectors
- `F1` PTC protection
- `D1` P6KE6.8CA bidirectional TVS protection
- bulk capacitors on the shared bus
- `Q1` AO3401A P-channel MOSFET for the electronics branch
- `F2` and `D2` for additional protection and USB backfeed isolation
- a separate `SYS_5V` rail for the ESP32 and ELRS receiver

The main goal is to keep the high current servo path from directly exposing the ESP32 and ELRS receiver to the same power faults.

### V3

V3 is planned around a buck regulator for the electronics rail. The goal is to make the ESP32 and ELRS receiver less dependent on the regulation quality of the external BEC.

## Firmware

The firmware is written for Arduino on the ESP32-C3. The source currently shown in this repository belongs to V1 and is also intended to run on the V2 hardware.

The main application:

- reads CRSF frames at **420000 baud**
- maps receiver channels to outputs
- generates **6 PWM channels at 50 Hz**
- applies predefined failsafe positions when the signal is lost
- provides serial diagnostics including frame count and CRC errors

The main sketch is kept modular and uses separate components for CRSF parsing, servo control and failsafe handling.

The current firmware source in the repository is the V1 firmware. The same firmware architecture is intended to be used with V2 hardware. V2 changes the power and protection circuitry, not the CRSF-to-PWM application logic.

The development build contains the supporting source files `config.h`, `crc.cpp/h`, `crsf.cpp/h`, `failsafe.cpp/h` and `servo.cpp/h`. These will be added to the repository as the source tree is cleaned up.

## Project structure

```text
OpenCRSF/
├── README.md
├── firmware/
│   └── OpenCRSF.ino.cpp
└── docs/
    ├── architecture.svg
    └── power-architecture-v2.svg
```

The actual V1/V2 schematics and hardware files will be added once the EasyEDA project files are organized. I am keeping the V1 firmware and V2 hardware documentation separate so the revisions are not mixed.

## Current status

| Revision | Status |
|---|---|
| V1 | Built and tested |
| V2 | Power architecture designed |
| V3 | Planned |

The project is still under development and I update the repository as new parts of the design are completed.

## What this project has involved

OpenCRSF has turned into a practical project covering embedded systems, RC electronics and hardware debugging:

**CRSF protocol** → **UART communication** → **PWM generation** → **failsafe logic** → **power distribution** → **protection circuits** → **PCB design**

The most useful part of the project has been taking a real hardware failure and using it to drive the next hardware revision.

## Author

**Efe Bostancı**

Electrical and Electronics Engineering student  
Interested in embedded systems, UAVs, RC electronics and PCB design.

[GitHub](https://github.com/Efe-Bostanci)

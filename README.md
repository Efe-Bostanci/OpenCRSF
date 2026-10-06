# OpenCRSF

A compact, from-scratch ESP32-C3 board that takes an ExpressLRS (CRSF) receiver's serial output and converts it into 6 standard PWM servo channels — built to work as a drop-in receiver for RC aircraft and vehicles, powered from any one of its 6 servo connectors, exactly like a standard RC receiver.

## Overview

- **MCU:** ESP32-C3 SuperMini
- **RF link:** ExpressLRS, received as CRSF over UART
- **Output:** 6× standard 3-pin PWM servo channels
- **Power input:** any of the 6 servo connectors can source power (ESC/BEC) — all six +5V pins are a single shared bus, so the board doesn't care which channel the battery/ESC is plugged into
- **Design tool:** EasyEDA

## Why this exists

Most RC receivers are closed, fixed-function boards. OpenCRSF is a ground-up, open design — the same CRSF-to-PWM job, but built and understood from the power section up, including real protection against the failure modes that actually happen in this hobby (reverse polarity, shared-bus faults, noisy BEC output under heavy load) rather than a single fuse and hoping for the best.

## Hardware revision history

### V1

First working revision. Powered from a single ESC/BEC, tested with up to 6 simultaneous servos and a brushless motor with no issues. Failed during a full-power test with a second, higher-current ESC driving a larger motor: the ELRS receiver overheated and was permanently destroyed.

Root cause, after investigation: V1's power section had only a PTC fuse, a TVS diode, and bulk capacitors sitting directly on the shared power rail — no protection against sustained BEC instability/noise under heavy load, and no reverse-polarity protection at all.

### V2 — current

Power section rebuilt around one key realization: with power allowed in from any of six connectors, there is only one real shared node (`VBUS`), and a series protection element (a fuse, a MOSFET) can never protect that shared node from itself — it can only gate a *separate, derived* branch. A shunt element (a TVS diode) is the only thing that protects the whole shared bus for free, regardless of which connector a fault enters from.

That distinction shaped the architecture:

- **`VBUS`** — the single shared node all 6 servo connectors' +5V pins tie to. Carries a PTC fuse (`F1`, 2.5A), a bidirectional TVS (`D1`, P6KE6.8CA), and bulk capacitance (1000µF + 100µF + 100nF). This protects the entire shared bus — every connector, every servo — for free, no matter which one the power enters from.
- **`Q1`** (AO3401A, P-channel MOSFET) gates a second, derived rail (`SYS_5V`) that exclusively feeds the ESP32 and the ELRS receiver. Correctly oriented — Drain toward the raw bus, Source toward the protected rail — so the MOSFET's own body diode blocks a reversed connection instead of quietly leaking it through to the electronics.
- **`F2`**, a second, smaller PTC fuse, and **`D2`**, a Schottky diode, further isolate the sensitive electronics branch — including blocking USB power from backfeeding into the main bus if the board is plugged into a computer for programming while still connected to a battery.

### V3 — planned

A buck regulator stage between the protected branch and the electronics, so the ESP32/ELRS no longer depend on the connected BEC's own regulation quality at all. This targets what's now believed to be the actual root cause of the V1 failure: a high-current ESC's BEC output becoming unstable under heavy load, rather than a simple reverse-polarity event.

## Status

Paused as of October 2026 while sourcing the final regulator component for V3. The V2 power section schematic is finalized and verified correct (MOSFET orientation, fuse placement, shared-bus vs. derived-branch protection, USB backfeed isolation); the V3 buck-converter addition is designed on paper but not yet built into a board revision.

## Repository contents

- `hardware/` — EasyEDA schematic exports
- More to come as the project resumes

## Author

**Efe Bostancı** — Electrical & Electronics Engineering student, İstanbul Aydın University. UAV/drone systems, PCB design, and embedded hardware.

[GitHub](https://github.com/Efe-Bostanci) · [LinkedIn](https://linkedin.com/in/efe-bostanci-0b3997233)
